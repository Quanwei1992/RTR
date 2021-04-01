#include "framework/Renderer.h"
#include "framework/Material.h"
#include "framework/Mesh.h"
#include "framework/MeshRender.h"
void Renderer::Render()
{
	for (const MeshRender* render : _meshRenders)
	{
		size_t numMtl = render->_materials.size();
		size_t numSubMesh = render->_mesh->GetSubMeshes().size();
		if (numMtl == 0 || numSubMesh == 0) continue;
		size_t mtlIndex = 0;
		for (size_t i = 0;i<numSubMesh;i++)
		{
			RenderSubMesh(render->_mesh->GetSubMeshes()[i], render->_materials[mtlIndex], render->GetWorld());
			mtlIndex++;
			if (mtlIndex = numMtl) { 
				mtlIndex = numMtl - 1;
			}
		}
	}
}

void Renderer::AddMeshRender(const MeshRender* render)
{
	_meshRenders.push_back(render);
}

void Renderer::SetView(const glm::mat4& viewMat)
{
	_viewMat = viewMat;
}

void Renderer::SetProj(const glm::mat4& projMat)
{
	_projMat = projMat;
}

void Renderer::Clear()
{
	_meshRenders.clear();
}

void Renderer::RenderSubMesh(SubMesh* mesh, Material* mtl, const glm::mat4& world)
{
	mtl->setMat4("RTR_VIEW", _viewMat);
	mtl->setMat4("RTR_PROJ", _projMat);
	mtl->setMat4("RTR_MODEL", world);
	mtl->setupShaderUniforms();
	mesh->Draw();
}
