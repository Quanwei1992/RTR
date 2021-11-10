#pragma once
#include "IApplication.hpp"
#include "GfxConfiguration.h"
namespace RTR
{
    class BaseApplication : implements IApplication
    {
    public:
        BaseApplication(GfxConfiguration& cfg);
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();
        virtual bool IsQuit();
        virtual GfxConfiguration& GetConfiguration();
	protected:
		virtual void OnDraw() {};
    protected:
        static bool m_bQuit;
        GfxConfiguration m_Config;
    private:
        BaseApplication(){};
    };
}