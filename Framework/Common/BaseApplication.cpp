#include "BaseApplication.hpp"

using namespace RTR;

bool RTR::BaseApplication::m_bQuit = false;
RTR::BaseApplication::BaseApplication(GfxConfiguration& cfg)
    :m_Config(cfg)
{

}
int RTR::BaseApplication::Initialize()
{
    m_bQuit = false;
    std::cout<<m_Config;
    return 0;
}

void RTR::BaseApplication::Finalize()
{

}

void RTR::BaseApplication::Tick()
{

}

bool RTR::BaseApplication::IsQuit()
{
    return m_bQuit;
}

GfxConfiguration RTR::BaseApplication::GetConfiguration()
{
    return m_Config;
}