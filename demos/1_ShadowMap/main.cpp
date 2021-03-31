#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "framework/application.h"
#include <framework/shader.h>
#include <framework/camera.h>
#include <framework/model.h>
#include <iostream>

#define SAFE_DELETE(x) if(x!=nullptr) delete x;x=nullptr

class MyApp : public Application
{

private:
	Camera _camera = Camera(glm::vec3(0.0, 2.5f, 6.0f));
	double _lastX = 0;
	double _lastY = 0;
	bool _firstMouse = true;
	Shader* _phongShader = nullptr;
	Shader* _whiteShader = nullptr;
	Model* _Marry = nullptr;
	Model* _Floor = nullptr;
	Mesh* _Cube = nullptr;


protected:
	bool Init() override
	{
		glfwSetInputMode(GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


		_lastX = GetWidth() / 2.0f;
		_lastY = GetHeight() / 2.0f;

		_phongShader = Shader::LoadShader("shaders/phong.vs", "shaders/phong.fs");
		if (_phongShader == nullptr) return false;

		_whiteShader = Shader::LoadShader("shaders/white.vs", "shaders/white.fs");
		if (_whiteShader == nullptr) return false;

		_Marry = Model::LoadModel("assets/mary/Marry.obj");
		if (_Marry == nullptr) return false;


		_Floor = Model::LoadModel("assets/floor/floor.obj");
		if (_Floor == nullptr) return false;

		_Cube = Mesh::Cube();

		return true;
	}


	void Update() override
	{

	}

	void Render() override
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	void OnExit() override
	{
		SAFE_DELETE(_phongShader);
		SAFE_DELETE(_whiteShader);
		SAFE_DELETE(_Marry);
		SAFE_DELETE(_Floor);
		SAFE_DELETE(_Cube);
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
			_camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			_camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			_camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			_camera.ProcessKeyboard(RIGHT, deltaTime);
	}

};



int main()
{
	MyApp app;
	return app.Run("ShadowMap", 1024, 768);
}