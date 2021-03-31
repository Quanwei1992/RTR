#include "framework/Renderer.h"

void Renderer::Render()
{

}

void Renderer::AddMeshRender(const MeshRender* render)
{

}

void Renderer::SetView(const glm::mat4& viewMat)
{
	_viewMat = viewMat;
}

void Renderer::SetProj(const glm::mat4& projMat)
{
	_projMat = projMat;
}
