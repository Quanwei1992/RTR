#pragma once
#include "glad/glad.h"
#include "GraphicsManager.hpp"
namespace RTR {
    class OpenGLGraphicsManager : public GraphicsManager
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
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;
    };
}