#include <windows.h>
#include <windowsx.h>
#include "BaseApplication.hpp"

namespace RTR
{
    class WindowsApplication : public BaseApplication
    {
    public:
        WindowsApplication(GfxConfiguration& config)
        :BaseApplication(config){};

        virtual int Initialize();
		virtual void Finalize();
		// One cycle of the main loop
        virtual void Tick();
        HWND GetMainWindow();
        
        // the WindowProc function prototype
        static LRESULT CALLBACK WindowProc(HWND hWnd,
            UINT message,
            WPARAM wParam,
            LPARAM lParam);
    private:
        HWND m_hWnd;

    };
}