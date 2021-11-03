#pragma once
#include "WindowsApplication.hpp"
#include "EGL/egl.h"
#include "GLES3/gl3.h"
namespace RTR
{
    class OpenGLESApplication : public WindowsApplication
    {
    public:
        OpenGLESApplication(GfxConfiguration& config)
        :WindowsApplication(config){};

        virtual int Initialize();
		virtual void Finalize();
		// One cycle of the main loop
        virtual void Tick();
		void SwapBuffer();
    private:
		HDC mHDC;
        EGLContext m_RenderContext;
		EGLDisplay m_Display;
    };
}