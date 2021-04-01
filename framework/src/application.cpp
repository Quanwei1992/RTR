#include "framework/application.h"
#include "framework/Mesh.h"
#include "framework/MeshRender.h"
#include "framework/Material.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->OnSizeChange(width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->OnMouse(xpos, ypos);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->OnScroll(xoffset, yoffset);
}



Application::Application()
	:_title("")
	, _width(0)
	, _height(0)
	, _window(nullptr)
{

}

Application::~Application()
{
	
}

int Application::Run(const std::string& title, int width, int height)
{

	_title = title;
	_width = width;
	_height = height;

	int ret = InitRenderEnv();
	if (ret != 0) return ret;

	glEnable(GL_DEPTH_TEST);

	if (!Init())
	{
		OnExit();
		glfwTerminate();
		return ret;
	}

	while (!glfwWindowShouldClose(_window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = (float)glfwGetTime();
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;
		ProcessInput(_window);
		Update();
		Render();
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	OnExit();
	glfwTerminate();
	_window = nullptr;
	return 0;
}


bool Application::Init()
{
	return true;
}

void Application::Update()
{

}

void Application::Render()
{

}

void Application::OnExit()
{

	for (MeshRender* render : _renders)
	{
		delete render;
	}
	_renders.clear();

	for (Material* mtl : _materials)
	{
		delete mtl;
	}
	_materials.clear();

	for (Mesh* mesh : _meshes)
	{
		delete mesh;
	}
	_meshes.clear();
}

void Application::OnSizeChange(int width, int height)
{
	_width = width;
	_height = height;
}

void Application::OnMouse(double x, double y)
{

}

void Application::OnScroll(double xoffset, double yoffset)
{

}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

float Application::GetDetaTime()
{
	return _deltaTime;
}

int Application::GetWidth()
{
	return _width;
}

int Application::GetHeight()
{
	return _height;
}

GLFWwindow* Application::GetWindow()
{
	return _window;
}

Mesh* Application::LoadMesh(const std::string& filename)
{
	Mesh* mesh = Mesh::Load(filename);
	_meshes.push_back(mesh);
	return mesh;
}

Material* Application::LoadMaterial(const std::string& filename)
{
	Material* mtl = Material::Load(filename);
	_materials.push_back(mtl);
	return mtl;
}

MeshRender* Application::CreateMeshRender(Mesh* mesh)
{
	MeshRender* render = new MeshRender(mesh);
	_renders.push_back(render);
	return render;
}

int Application::InitRenderEnv()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowUserPointer(_window, this);
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, Application::framebuffer_size_callback);
	glfwSetCursorPosCallback(_window, Application::mouse_callback);
	glfwSetScrollCallback(_window, Application::scroll_callback);


	// glad: load all OpenGL function pointers
// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}



