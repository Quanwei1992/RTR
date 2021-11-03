#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include "OpenGLESGraphicsManager.hpp"
#include "OpenGLESApplication.hpp"
using namespace RTR;

namespace RTR
{
	extern IApplication* g_pApp;
}

int RTR::OpenGLESGraphicsManager::Initialize()
{
	glViewport(0, 0, 960, 540);
	int error = glGetError();
	if (error != 0)return error;
	error = InitShader();
	if (error != 0)return error;
	InitVB();

	return error;
}

void RTR::OpenGLESGraphicsManager::Finalize()
{

}

void RTR::OpenGLESGraphicsManager::Tick()
{
	OpenGLESApplication* app = reinterpret_cast<OpenGLESApplication*>(g_pApp);
	Render();
	app->SwapBuffer();
}

int RTR::OpenGLESGraphicsManager::InitShader()
{

	std::string vertexPath = R"(Assets\Shader\diffuse_vs.elsl)";
	std::string fragmentPath = R"(Assets\Shader\diffuse_ps.elsl)";

	// 1.���ļ�·���л�ȡ����/Ƭ����ɫ��
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	try
	{
		// ���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return -1;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint sucess;
	GLchar infoLog[512];

	// ������ɫ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &sucess);
	if (!sucess) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Ƭ����ɫ��
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucess);
	if (!sucess) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
	if (!sucess) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::ShaderProgram::LINK_FAILED\n" << infoLog << std::endl;
	}

	m_ShaderProgram = shaderProgram;
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return 0;
}

void RTR::OpenGLESGraphicsManager::InitVB()
{
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint attr_apos = glGetAttribLocation(m_ShaderProgram, "aPos");
	glEnableVertexAttribArray(attr_apos);
	glVertexAttribPointer(attr_apos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RTR::OpenGLESGraphicsManager::Render()
{
	GLenum ret = GL_NO_ERROR;

	glUseProgram(m_ShaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glFlush();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

