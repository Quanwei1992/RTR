#pragma once
#include "WindowsApplication.hpp"

namespace RTR
{
    class OpenGLApplication : public WindowsApplication
    {

    public:
		OpenGLApplication(GfxConfiguration& config)
			: WindowsApplication(config) {};
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();
		void SwapBuffer();
    private:
        HGLRC m_RenderContext;
		HDC m_Hdc;
    };
}