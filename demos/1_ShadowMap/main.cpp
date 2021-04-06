#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "framework/Application.h"
#include "framework/Shader.h"
#include "framework/Camera.h"
#include "framework/Mesh.h"
#include "framework/Material.h"
#include "framework/GameObject.h"
#include "framework/Renderer.h"
#include "framework/MeshRender.h"

#include <iostream>

#define SAFE_DELETE(x) if(x!=nullptr) delete x;x=nullptr
#define CHECK_NULL(x) if(x==nullptr) return false

class MyApp : public Application
{

private:
	Camera _camera = Camera(glm::vec3(0.0, 2.5f, 6.0f));
	double _lastX = 0;
	double _lastY = 0;
	bool _firstMouse = true;
	GameObject _marry = GameObject("Marry");
	GameObject _light = GameObject("Light");
	GameObject _floor = GameObject("Floor");
	Renderer _renderer;
	Material* _marryMtl = nullptr;

protected:
	bool Init() override
	{
		glfwSetInputMode(GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


		_lastX = GetWidth() / 2.0f;
		_lastY = GetHeight() / 2.0f;


		Mesh* mesh = LoadMesh("assets/models/marry/Marry.obj");
		Material* mtl = LoadMaterial("assets/materials/marry.json");
		MeshRender* render = CreateMeshRender(mesh);
		render->AddMaterial(mtl);
		_marry.SetMeshRender(render);
		_marryMtl = mtl;
		_marryMtl->setFloat("uLightIntensity", 1.0f);

		mesh = Mesh::Cube();
		mtl = LoadMaterial("assets/materials/lightCube.json");
		render = CreateMeshRender(mesh);
		render->AddMaterial(mtl);
		_light.SetMeshRender(render);
		_light.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

		mesh = LoadMesh("assets/models/floor/floor.obj");
		mtl = LoadMaterial("assets/materials/floor.json");
		render = CreateMeshRender(mesh);
		render->AddMaterial(mtl);
		_floor.SetMeshRender(render);
	
		return true;
	}


	void Update() override
	{
		glm::vec3 lightPos(0, 0, 0);
		double timer = glfwGetTime() * 0.5;
		lightPos.x = glm::sin(timer * 3) * 2;
		lightPos.y = glm::cos(timer * 2) * 2.5;
		lightPos.z = glm::cos(timer) * 2;
		_light.SetPosition(lightPos);
	}

	void Render() override
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(_camera.Zoom), (float)GetWidth() / (float)GetHeight(), 0.1f, 1000.0f);
		glm::mat4 view = _camera.GetViewMatrix();

		_marryMtl->setVec3("uLightPos", _light.GetPosition());
		_marryMtl->setVec3("uCameraPos", _camera.Position);

		_renderer.Clear();
		_renderer.SetProj(projection);
		_renderer.SetView(view);

		_renderer.AddMeshRender(_floor.GetMeshRender());
		_renderer.AddMeshRender(_marry.GetMeshRender());
		_renderer.AddMeshRender(_light.GetMeshRender());
		_renderer.Render();


	}


	void OnExit() override
	{
		//SAFE_DELETE(_phongShader);
		//SAFE_DELETE(_whiteShader);
		//SAFE_DELETE(_Marry);
		//SAFE_DELETE(_Cube);
	}


	void OnSizeChange(int width, int height) override
	{
		Application::OnSizeChange(width, height);
		glViewport(0, 0, width, height);
	}


	void OnMouse(double xpos, double ypos) override
	{
		Application::OnMouse(xpos, ypos);
		if (_firstMouse)
		{
			_lastX = xpos;
			_lastY = ypos;
			_firstMouse = false;
		}

		double xoffset = xpos - _lastX;
		double yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top

		_lastX = xpos;
		_lastY = ypos;

		_camera.ProcessMouseMovement((float)xoffset, (float)yoffset);
	}


	void OnScroll(double xoffset, double yoffset) override
	{
		Application::OnScroll(xoffset, yoffset);
		_camera.ProcessMouseScroll((float)yoffset);
	}


	void ProcessInput(GLFWwindow* window) override
	{
		Application::ProcessInput(window);
		float deltaTime = GetDetaTime();
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			_camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			_camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			_camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			_camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	}

};



int main()
{
	MyApp app;
	return app.Run("Hello world", 1024, 768);
}