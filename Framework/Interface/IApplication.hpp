#pragma once
#include "Interface.hpp"
#include "IRuntimeModule.hpp"
namespace RTR
{
    Interface IApplication : implements IRuntimeModule
    {
    public:
        virtual int Initialize() = 0;
        virtual void Finalize() = 0;
        virtual void Tick() = 0;
        virtual bool IsQuit() = 0;

    };
}
