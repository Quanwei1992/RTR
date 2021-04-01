#pragma once
#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include <string>
#include <vector>
struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh;

class SubMesh
{
public:
    SubMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void Draw();
private:
    friend class Mesh;
	// mesh Data
	std::vector<Vertex>  vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO;
	// render data 
	unsigned int VBO, EBO;
	// initializes all the buffer objects/arrays
	void SetupMesh();
 
};


class Mesh 
{
public:
    ~Mesh();
    const  std::vector<SubMesh*>& GetSubMeshes() const;

public: 
    static Mesh* Load(const std::string& filename);
    static Mesh* Cube();

private:
    std::vector<SubMesh*> _subMeshes;

};
