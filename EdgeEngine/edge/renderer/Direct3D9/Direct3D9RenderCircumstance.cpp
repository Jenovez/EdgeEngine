// cpp文件

#include "Direct3D9RenderCircumstance.h"
#include <platform/win32/Win32Window.h>

USING_NS_EDGE;

Direct3D9RenderCircumstance::Direct3D9RenderCircumstance()
: m_pDevice(NULL)
, _bgColor(Color::BLACK)
{
}

Direct3D9RenderCircumstance::~Direct3D9RenderCircumstance()
{
	D3D9::SafeRelease(&m_pDevice);
}

bool Direct3D9RenderCircumstance::initRenderer(IWindow* window, const Color& bgColor)
{
	Win32Window* win32Window = dynamic_cast<Win32Window*>(window);
	if (!win32Window) { return false; }

	_bgColor = bgColor;
	HWND hWnd = win32Window->getHWND();
	const Size& clientSize = win32Window->getClientSize();

	HRESULT hr = NULL;

	LPDIRECT3D9 pD3D = 0;
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	DWORD behaviorFlags = 0;
	hr = pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (SUCCEEDED(hr))
	{
		// 如果支持硬件顶点运算就设置使用硬件,否则使用软件模拟
		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		{
			behaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}
		else
		{
			behaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		// 显示器刷新频率
		// 参数1:D3DPRESENT_INTERVAL_IMMEDIATE 实时刷新
		// 参数2:D3DPRESENT_INTERVAL_DEFAULT 根据显示器的刷新率刷新
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		d3dpp.Windowed = !win32Window->isFullScreen();
		d3dpp.hDeviceWindow = hWnd;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // 窗口模式这个值必须是0
		// 窗口模式这两个值可以不填,默认是窗口大小,全屏下必须指定一个显卡所支持的分辨率
		d3dpp.BackBufferWidth = (UINT)clientSize.width;
		d3dpp.BackBufferHeight = (UINT)clientSize.height;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = 0;

		hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			hWnd, behaviorFlags, &d3dpp, &m_pDevice);
	}

	if (SUCCEEDED(hr))
	{
		//关闭背面消隐
		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		// 设置高洛德着色模式
		m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		// 设置为实体渲染
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		// 设置纹理
		m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		// alpha透明
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		// 开启alpha混合
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		// 关闭颜色混合
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// 关闭灯光
		m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// 设置为线性纹理过滤(d3d默认的是临近点采样)
		if (behaviorFlags == D3DCREATE_HARDWARE_VERTEXPROCESSING)
		{
			m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXTUREFILTERTYPE::D3DTEXF_LINEAR);
			m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXTUREFILTERTYPE::D3DTEXF_LINEAR);
		}
	}

	// 设置为左上角(0,0)坐标系
	D3DXMATRIX pixelProjection;
	D3DXMATRIX viewMatrix;
	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixOrthoOffCenterLH(&pixelProjection, 0.0f, (FLOAT)clientSize.width, (FLOAT)clientSize.height, 0.0f, 0.0f, 1.0f);
	m_pDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &pixelProjection);

	D3D9::SafeRelease(&pD3D);

	return SUCCEEDED(hr);
}

void Direct3D9RenderCircumstance::beginDraw()
{
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a), 1.0f, 0);
	m_pDevice->BeginScene();
}

void Direct3D9RenderCircumstance::endDraw()
{
	m_pDevice->EndScene();
	m_pDevice->Present(0, 0, 0, 0);
}

IDirect3DDevice9* Direct3D9RenderCircumstance::getDirect3DDevice9() const { return m_pDevice; }
