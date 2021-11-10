#pragma once
#include <d2d1.h>
#include "GraphicsManager.hpp"

RTR_BEGIN_NAMESPACE

class D2DGraphicsManager : public GraphicsManager
{
public:
	virtual int Initialize();
	virtual void Finalize();

	virtual void Tick();
protected:
	HRESULT CreateGraphicsResources();
protected:
	ID2D1Factory* m_pFactory = nullptr;
	ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
};

RTR_END_NAMESPACE

