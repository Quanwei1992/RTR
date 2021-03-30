#pragma once
#include <string>
struct GLFWwindow;

class Application
{
public:
	Application();
	virtual ~Application();
	int Run(const std::string& title, int width, int height);

protected:
	virtual bool Init();
	virtual void Update();
	virtual void Render();
	virtual void OnExit();
	virtual void OnSizeChange(int width, int height);
	virtual void OnMouse(double x, double y);
	virtual void OnScroll(double xoffset, double yoffset);
	virtual void ProcessInput(GLFWwindow* window);
	float GetDetaTime();
	int GetWidth();
	int GetHeight();
	GLFWwindow* GetWindow();

private:
	int InitRenderEnv();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
	std::string _title;
	int _width;
	int _height;
	GLFWwindow* _window;
	float _deltaTime = 0.0f;
	float _lastFrame = 0.0f;

};