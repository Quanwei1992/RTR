#include "framework/MeshRender.h"


MeshRender::MeshRender(Mesh* mesh)
	:_mesh(mesh)
{

}

void MeshRender::AddMaterial(Material* mtl)
{
	_materials.push_back(mtl);
}
