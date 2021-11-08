
#include "WindowsApplication.hpp"
#include "D3D9GraphicsManager.hpp"
#include "MemoryManager.hpp"
#include <tchar.h>

using namespace RTR;
namespace RTR
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, L"RTREngine (Windows d3d9)");
    IApplication* g_pApp = static_cast<IApplication*>(new WindowsApplication(config));
    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new D3D9GraphicsManager);
    MemoryManager* g_pMemoryManager = new MemoryManager;
}
