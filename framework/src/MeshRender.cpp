#include "framework/MeshRender.h"


MeshRender::MeshRender(Mesh* mesh)
	:_mesh(mesh)
	,_world(1.0f)
{

}

void MeshRender::AddMaterial(Material* mtl)
{
	_materials.push_back(mtl);
}

void MeshRender::SetWorld(const glm::mat4& mat)
{
	_world = mat;
}

const glm::mat4& MeshRender::GetWorld() const
{
	return _world;
}
