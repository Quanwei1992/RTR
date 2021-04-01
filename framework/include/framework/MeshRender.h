#pragma once
#include "glm/glm.hpp"
#include <vector>

class Material;
class Mesh;
class Renderer;
class MeshRender
{
public:
	MeshRender() = delete;
	MeshRender(Mesh* mesh);
	void AddMaterial(Material* mtl);
	void SetWorld(const glm::mat4& mat);
	const glm::mat4& GetWorld() const;
	

private:
	friend class Renderer;
	std::vector<Material*> _materials;
	Mesh* _mesh;
	glm::mat4 _world;
};