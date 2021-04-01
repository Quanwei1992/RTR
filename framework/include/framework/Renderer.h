#pragma once
#include "glm/glm.hpp"
#include <vector>
class MeshRender;
class SubMesh;
class Material;
class Renderer
{
public:
	void Render();
	void AddMeshRender(const MeshRender* render);
	void SetView(const glm::mat4& viewMat);
	void SetProj(const glm::mat4& projMat);
	void Clear();

protected:
	void RenderSubMesh(SubMesh* mesh, Material* mtl, const glm::mat4& world);

private:
	glm::mat4 _viewMat;
	glm::mat4 _projMat;
	std::vector<const MeshRender*> _meshRenders;
};
