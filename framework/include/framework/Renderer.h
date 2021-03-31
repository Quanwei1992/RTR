#pragma once
#include "glm/glm.hpp"
#include <vector>
class MeshRender;
class Renderer
{
public:
	void Render();
	void AddMeshRender(const MeshRender* render);
	void SetView(const glm::mat4& viewMat);
	void SetProj(const glm::mat4& projMat);

private:
	glm::mat4 _viewMat;
	glm::mat4 _projMat;
	std::vector<const MeshRender*> _meshRenders;
};
