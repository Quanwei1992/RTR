#include "D3D9GraphicsManager.hpp"
#include "WindowsApplication.hpp"
#include <mmsystem.h>
#include <string>
using namespace RTR;
namespace RTR
{
    extern IApplication* g_pApp;
    
    template<class T>
    inline void SafeRelease(T **ppInterfaceToRelease)
    {
        if (*ppInterfaceToRelease != nullptr)
        {
            (*ppInterfaceToRelease)->Release();

            (*ppInterfaceToRelease) = nullptr;
        }
    }


	struct CUSTOMVERTEX
	{
		FLOAT x, y, z;
		DWORD color;
	};
	// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ)

}

RTR::D3D9GraphicsManager::D3D9GraphicsManager():
    m_pD3D(nullptr),
    m_pDevice(nullptr)
{

}

int RTR::D3D9GraphicsManager::Initialize()
{
    int result = 0;
    result = GraphicsManager::Initialize();
    if(result!=0)return result;

    result = static_cast<int>(InitD3D());
    return result;
}

void RTR::D3D9GraphicsManager::Tick()
{
    Render();
}

void RTR::D3D9GraphicsManager::Finalize()
{
    ClearupD3D();
}


HRESULT RTR::D3D9GraphicsManager::InitD3D()
{


    HWND hWnd = reinterpret_cast<WindowsApplication*>(g_pApp)->GetMainWindow();


    // Create the D3D object, which is needed to create the D3DDevice.
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if(m_pD3D == nullptr) return E_FAIL;
    
    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp,sizeof(d3dpp));

    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;


    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &m_pDevice ) ) )
        {
        return E_FAIL;
    }

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    return InitShader();
}

HRESULT RTR::D3D9GraphicsManager::InitVB()
{
	HRESULT hr = S_OK;
	// Vertex Buffer
	{	
		D3DXVECTOR3 vertices[] =
		{
			{ 0.5f,  0.5f, 0.0f },  // top right
			{ 0.5f, -0.5f, 0.0f },  // bottom right
			{ -0.5f, -0.5f, 0.0f },  // bottom left
			{ -0.5f,  0.5f, 0.0f }   // top left 
		};
		hr = m_pDevice->CreateVertexBuffer(4 * sizeof(D3DXVECTOR3), 0, 0, D3DPOOL_DEFAULT, &m_pVB, NULL);
		if (FAILED(hr)) return hr;

		D3DXVECTOR2* pVertices = nullptr;
		hr = m_pVB->Lock(0, 0, (void**)&pVertices, 0);
		if (FAILED(hr)) return hr;
		memcpy_s(pVertices, sizeof(vertices), vertices, sizeof(vertices));
		hr = m_pVB->Unlock();
		if (FAILED(hr)) return hr;
	}

	// Index Buffer
	{
		WORD indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		hr = m_pDevice->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);
		if (FAILED(hr)) return hr;
		WORD* pIndices = NULL;
		hr = m_pIB->Lock(0, sizeof(indices), (void**)&pIndices, 0);
		if (FAILED(hr)) return hr;
		memcpy_s(pIndices, sizeof(indices), indices, sizeof(indices));
		hr = m_pIB->Unlock();
		if (FAILED(hr)) return hr;
	}

	return S_OK;
}

HRESULT RTR::D3D9GraphicsManager::InitShader()
{
	HRESULT hr = S_OK;
	LPD3DXBUFFER pError = nullptr;
	LPD3DXBUFFER pCode = nullptr;
	char errInfo[256] = { 0 };
	// Vertex Declaration
	{
		D3DVERTEXELEMENT9  decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_POSITION ,0 },
			D3DDECL_END()
		};

		hr = m_pDevice->CreateVertexDeclaration(decl, &m_pVertexDeclaration);
		if (FAILED(hr)) {
			return hr;
		}

	}

	// Vertex Shader
	{
		std::string vsPath = R"(Assets\Shader\diffuse_vs.hlsl)";
		hr = D3DXCompileShaderFromFile(vsPath.c_str(), NULL, NULL, "VSMain", "vs_2_0", D3DXSHADER_DEBUG, &pCode, &pError, &m_pConstantTable);
		if (FAILED(hr)) {			
			if (pError) {		
				strcpy(errInfo, (char*)pError->GetBufferPointer());
			}
			SafeRelease(&pError);
			SafeRelease(&pCode);
			return hr;
		}

		hr = m_pDevice->CreateVertexShader((DWORD*)pCode->GetBufferPointer(), &m_pVertexShader);
		SafeRelease(&pError);
		SafeRelease(&pCode);
		if (FAILED(hr)) {
			return hr;
		}
	}

	// Pixel Shader
	{
		std::string psPath = R"(Assets\Shader\diffuse_ps.hlsl)";
		hr = D3DXCompileShaderFromFile(psPath.c_str(), NULL, NULL, "PSMain", "ps_2_0", D3DXSHADER_DEBUG, &pCode, &pError, NULL);
		if (FAILED(hr)) {
			if (pError) {
				strcpy(errInfo, (char*)pError->GetBufferPointer());
			}
			SafeRelease(&pError);
			SafeRelease(&pCode);
			return hr;
		}
		hr = m_pDevice->CreatePixelShader((DWORD*)pCode->GetBufferPointer(), &m_pPixelShader);
		SafeRelease(&pError);
		SafeRelease(&pCode);
		if (FAILED(hr)) {
			return hr;
		}
	}
	return InitVB();
}

void RTR::D3D9GraphicsManager::SetupMatrices()
{
	// For our world matrix, we will just rotate the object about the y-axis.
	D3DXMATRIXA16 matWorld;

	// Set up the rotation matrix to generate 1 full rotation (2*PI radians) 
	// every 1000 ms. To avoid the loss of precision inherent in very high 
	// floating point numbers, the system time is modulated by the rotation 
	// period before conversion to a radian angle.
	UINT iTime = timeGetTime() % 1000;
	FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
	D3DXMatrixRotationY(&matWorld, fAngle);
	//m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	//m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	//m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMATRIXA16 wvp = matWorld * matView * matProj;
	//D3DXHANDLE WVPMatrixHandle = m_pEffect->GetParameterByName(0, "g_mvp");

	//HRESULT hr = m_pEffect->SetMatrix(WVPMatrixHandle, &wvp);


}



void RTR::D3D9GraphicsManager::ClearupD3D()
{
	SafeRelease(&m_pPixelShader);
	SafeRelease(&m_pVertexShader);
	SafeRelease(&m_pVertexDeclaration);
	SafeRelease(&m_pVB);
    SafeRelease(&m_pDevice);
    SafeRelease(&m_pD3D);
}

void RTR::D3D9GraphicsManager::Render()
{

	if (m_pDevice == nullptr) return;
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	HRESULT hr = S_OK;
    if( SUCCEEDED( m_pDevice->BeginScene() ) )
    {
		hr = m_pDevice->SetVertexDeclaration(m_pVertexDeclaration);
		hr = m_pDevice->SetVertexShader(m_pVertexShader);
		hr = m_pDevice->SetPixelShader(m_pPixelShader);
		hr = m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(D3DXVECTOR3));
		hr = m_pDevice->SetIndices(m_pIB);
		hr = m_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		hr = m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 6/3);
        m_pDevice->EndScene();
    }

     // Present the backbuffer contents to the display
    m_pDevice->Present( NULL, NULL, NULL, NULL );
}