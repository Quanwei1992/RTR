#include <stdio.h>
#include "IApplication.hpp"
#include "GraphicsManager.hpp"
#include "MemoryManager.hpp"
using namespace RTR;
namespace RTR
{
	extern IApplication* g_pApp;
	extern GraphicsManager* g_pGraphicsManager;
	extern MemoryManager* g_pMemoryManager;
}

int main(int argc,char** argv)
{
	int ret;
	ret = g_pApp->Initialize();
	if(ret!=0){
		printf("App Initialize failed,will exit now.");
		return ret;
	}

	ret = g_pMemoryManager->Initialize();
	if(ret!=0){
		printf("MemoryManager Initialize failed,will exit now.");
		return ret;
	}

	if ((ret = g_pGraphicsManager->Initialize()) != 0) {
		printf("Graphics Manager Initialize failed, will exit now.");
		return ret;
	}	

	while(!g_pApp->IsQuit()){
		g_pApp->Tick();
		g_pMemoryManager->Tick();
		g_pGraphicsManager->Tick();
	}
	g_pGraphicsManager->Finalize();
	g_pMemoryManager->Finalize();
	g_pApp->Finalize();
	return 0;
}