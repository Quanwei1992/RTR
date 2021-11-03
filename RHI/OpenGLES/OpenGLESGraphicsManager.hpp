#pragma once
#include "GraphicsManager.hpp"

namespace RTR
{
	class OpenGLESGraphicsManager : public GraphicsManager
	{
	public:
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
	private:
		int InitShader();
		void InitVB();
		void Render();
	private:
		GLuint m_ShaderProgram;
		//GLuint m_VAO; not support on es2.0
		GLuint m_VBO;
		GLuint m_EBO;

	};
}