#pragma once
#include <vector>
class Material;
class Mesh;

class MeshRender
{
public:
	MeshRender() = delete;
	MeshRender(Mesh* mesh);
	void AddMaterial(Material* mtl);
	

private:
	std::vector<Material*> _materials;
	Mesh* _mesh;
};