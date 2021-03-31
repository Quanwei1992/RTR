#include "framework/mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

SubMesh::SubMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	this->vertices = vertices;
	this->indices = indices;
	SetupMesh();
}

void SubMesh::Draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}

Mesh* Mesh::Cube()
{
	std::vector<Vertex> vertices = {
		// Front face
		{{-1.0, -1.0, 1.0  }},
		{{1.0, -1.0, 1.0   }},
		{{1.0, 1.0, 1.0    }},
		{{-1.0, 1.0, 1.0   }},

		// Back face
		{{-1.0, -1.0, -1.0 }},
		{{-1.0, 1.0, -1.0  }},
		{{1.0, 1.0, -1.0   }},
		{{1.0, -1.0, -1.0  }},

		// Top face     
		{{-1.0, 1.0, -1.0  }},
		{{-1.0, 1.0, 1.0   }},
		{{1.0, 1.0, 1.0    }},
		{{1.0, 1.0, -1.0   }},

		// Bottom face 
		{{-1.0, -1.0, -1.0 }},
		{{1.0, -1.0, -1.0  }},
		{{1.0, -1.0, 1.0   }},
		{{-1.0, -1.0, 1.0  }},

		// Right face 
		{{1.0, -1.0, -1.0  }},
		{{1.0, 1.0, -1.0   }},
		{{1.0, 1.0, 1.0    }},
		{{1.0, -1.0, 1.0   }},

		// Left face  
		{{-1.0, -1.0, -1.0 }},
		{{-1.0, -1.0, 1.0  }},
		{{-1.0, 1.0, 1.0   }},
		{{-1.0, 1.0, -1.0  }},
	};
	std::vector<unsigned int> indices = {
			0, 1, 2, 0, 2, 3,    // front
			4, 5, 6, 4, 6, 7,    // back
			8, 9, 10, 8, 10, 11,   // top
			12, 13, 14, 12, 14, 15,   // bottom
			16, 17, 18, 16, 18, 19,   // right
			20, 21, 22, 20, 22, 23,   // left	
	};
	Mesh* cube = new Mesh();
	SubMesh* subMesh = new SubMesh(vertices, indices);
	cube->_subMeshes.push_back(subMesh);
	return cube;
}



SubMesh* process_mesh(aiMesh* mesh, const aiScene* scene)
{
	// data to fill
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// normals
		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
			// tangent
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
			// bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	return new SubMesh(vertices, indices);
}


void process_node(std::vector<SubMesh*>& meshes,aiNode* node, const aiScene* scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(process_mesh(mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		process_node(meshes,node->mChildren[i], scene);
	}
}


Mesh::~Mesh()
{
	for (auto subMesh : _subMeshes)
	{
		delete subMesh;
	}
	_subMeshes.clear();
}

Mesh* Mesh::Load(const std::string& filename)
{
	std::vector<SubMesh*> meshes;
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return nullptr;
	}
	Mesh* mesh = new Mesh;
	process_node(mesh->_subMeshes, scene->mRootNode, scene);
	return mesh;
}

void SubMesh::SetupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}

