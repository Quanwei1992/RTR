#include <stdio.h>
#include <tchar.h>
#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include "MemoryManager.hpp"
#include "GraphicsManager.hpp"
#include "OpenGlESApplication.hpp"
#include "OpenGLES/OpenGLESGraphicsManager.hpp"

using namespace RTR;
namespace RTR {
	GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540,L"RTREngine (Windows opengl-es 2.0)");
	IApplication* g_pApp                = static_cast<IApplication*>(new OpenGLESApplication(config));
    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new OpenGLESGraphicsManager);
    MemoryManager*   g_pMemoryManager   = static_cast<MemoryManager*>(new MemoryManager);
}

int RTR::OpenGLESApplication::Initialize()
{
    int result = 0;
    result = WindowsApplication::Initialize();
    if(result!=0){
        printf("Windows Application initialize failed!");
        return result;
    }

    HDC hdc = GetDC(GetMainWindow());
	mHDC = hdc;
    EGLDisplay eglDisplay = eglGetDisplay(hdc);
    EGLint eglVersionMajor,eglVersionMinor;
	if (!eglInitialize(eglDisplay, &eglVersionMajor, &eglVersionMinor)) {
		int error = eglGetError();
		return error;
	}
	if (!eglBindAPI(EGL_OPENGL_ES_API)) {
		int error = eglGetError();
		return error;
	}

	EGLint const attrib_list[] = {
		EGL_RED_SIZE, GetConfiguration().redBits,
		EGL_GREEN_SIZE, GetConfiguration().greenBits,
		EGL_BLUE_SIZE, GetConfiguration().blueBits,
		EGL_NONE
	};

    EGLint numConfigs;
    EGLConfig windowConfig;
	if (!eglChooseConfig(eglDisplay, attrib_list, &windowConfig, 1, &numConfigs)) {
		int error = eglGetError();
		return error;
	}

    EGLint surfaceAttributes[] = { EGL_NONE };
    EGLSurface eglSurface = eglCreateWindowSurface(eglDisplay, windowConfig, GetMainWindow(), surfaceAttributes);

    EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext eglContext = eglCreateContext(eglDisplay, windowConfig, NULL, contextAttributes);

	if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
		return -1;
	}

	m_RenderContext = eglContext;
	m_Display = eglDisplay;

	return 0;
}

void RTR::OpenGLESApplication::Finalize()
{
    if (m_RenderContext) {
        eglMakeCurrent(NULL,NULL,NULL,NULL);
        eglDestroyContext(m_Display,m_RenderContext);
        m_RenderContext = nullptr;
		m_Display = nullptr;
    }

    WindowsApplication::Finalize();
}

void RTR::OpenGLESApplication::Tick()
{
    WindowsApplication::Tick();
}

void RTR::OpenGLESApplication::SwapBuffer()
{
	SwapBuffers(mHDC);
}