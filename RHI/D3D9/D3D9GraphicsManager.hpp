#pragma once
#include <stdint.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <strsafe.h>
#include "GraphicsManager.hpp"

namespace RTR
{
    class D3D9GraphicsManager : public GraphicsManager
    {
    public:
        D3D9GraphicsManager();
        virtual int Initialize();
	    virtual void Finalize();
        virtual void Tick();
    
    private:
        HRESULT InitD3D();
		HRESULT InitVB();
		HRESULT InitShader();
		void SetupMatrices();
        void ClearupD3D();
        void Render();
    private:
        LPDIRECT3D9 m_pD3D;
        LPDIRECT3DDEVICE9 m_pDevice;
		LPDIRECT3DVERTEXBUFFER9 m_pVB; // Buffer to hold vertices
		LPDIRECT3DINDEXBUFFER9 m_pIB;
		LPDIRECT3DVERTEXSHADER9 m_pVertexShader;
		LPDIRECT3DPIXELSHADER9 m_pPixelShader;
		LPD3DXCONSTANTTABLE m_pConstantTable;
		LPDIRECT3DVERTEXDECLARATION9 m_pVertexDeclaration;
    };
}