#include "framework/GameObject.h"
#include "framework/MeshRender.h"
#include <glm/gtc/matrix_transform.hpp>
GameObject::GameObject(const std::string& name)
	:_position(0,0,0)
	,_scale(1,1,1)
	,_wordMat(1.0f)
	,_render(nullptr)
{

}

void GameObject::SetMeshRender(MeshRender* render)
{
	_render = render;
}

const MeshRender* GameObject::GetMeshRender() const
{
	return _render;
}

const glm::mat4& GameObject::GetWorld() const
{
	return _wordMat;
}

void GameObject::updateWorldMat()
{
	_wordMat = glm::mat4(1.0f);
	_wordMat = glm::translate(_wordMat, _position);
	_wordMat = glm::scale(_wordMat, _scale);
	if (_render != nullptr)
	{
		_render->SetWorld(_wordMat);
	}
}

void GameObject::SetPosition(const glm::vec3& pos)
{
	_position = pos;
	updateWorldMat();
}

void GameObject::SetScale(const glm::vec3& scale)
{
	_scale = scale;
	updateWorldMat();
}

const glm::vec3& GameObject::GetPosition() const
{
	return _position;
}

const glm::vec3& GameObject::GetScale() const
{
	return _scale;
}

