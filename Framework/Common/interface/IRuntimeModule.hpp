#pragma once
#include "Interface.hpp"

RTR_BEGIN_NAMESPACE

Interface IRuntimeModule
{
public:
    virtual ~IRuntimeModule(){};
    virtual int Initialize() = 0;
    virtual void Finalize() = 0;
    virtual void Tick() = 0;
};

RTR_END_NAMESPACE