#include "framework/mesh.h"

using namespace std;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	// now that we have all the required data, set the vertex buffers and its attribute pointers.
	setupMesh();
}

void Mesh::Draw(Shader& shader)
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT,0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
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
	std::vector<Texture> textures;
	Mesh* cube = new Mesh(vertices, indices, textures);
	return cube;
}

void Mesh::setupMesh()
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
