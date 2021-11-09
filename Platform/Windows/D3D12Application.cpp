#include "WindowsApplication.hpp"
#include "D3D12GraphicsManager.hpp"
#include "MemoryManager.hpp"
#include <tchar.h>

using namespace RTR;

namespace RTR {
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, _T("RTREngine (Windows d3d12)"));
	IApplication* g_pApp                = static_cast<IApplication*>(new WindowsApplication(config));
    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new D3D12GraphicsManager);
    MemoryManager*   g_pMemoryManager   = static_cast<MemoryManager*>(new MemoryManager);

}

