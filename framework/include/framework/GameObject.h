#pragma once
#include "glm/glm.hpp"
#include <string>
#include <vector>

class MeshRender;
class GameObject
{
public:
	GameObject(const std::string& name);
	void SetMeshRender (MeshRender* render);

	void SetPosition(const glm::vec3& pos);
	void SetScale(const glm::vec3& scale);
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetScale() const;
	const MeshRender* GetMeshRender() const;
	const glm::mat4& GetWorld() const;

protected:
	void updateWorldMat();

private:
	std::string _name;
	glm::vec3 _position;
	glm::vec3 _scale;
	glm::mat4 _wordMat;
	MeshRender* _render;
};