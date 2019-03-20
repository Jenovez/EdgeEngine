// cpp文件

#include "Direct2DRenderCircumstance.h"
#include <platform/win32/Win32Window.h>

USING_NS_EDGE;

Direct2DRenderCircumstance::Direct2DRenderCircumstance()
: _d2dFactory(NULL)
, _d2dRenderTarget(NULL)
, _dwFactory(NULL)
, _wicImagingFactory(NULL)
, _bgColor(Color::BLACK)
{
}

Direct2DRenderCircumstance::~Direct2DRenderCircumstance()
{
	D2D1::SafeRelease(&_wicImagingFactory);
	D2D1::SafeRelease(&_dwFactory);
	D2D1::SafeRelease(&_d2dRenderTarget);
	D2D1::SafeRelease(&_d2dFactory);
}

bool Direct2DRenderCircumstance::initRenderer(IWindow* window, const Color& bgColor)
{
	Win32Window* win32Window = dynamic_cast<Win32Window*>(window);
	if (!win32Window) { return false; }

	_bgColor = bgColor;
	HWND hwnd = win32Window->getHWND();
	const Size& clientSize = win32Window->getClientSize();

	HRESULT hr = NULL;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_d2dFactory);

	if (SUCCEEDED(hr))
	{
		hr = _d2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd,
			D2D1::SizeU((UINT32)clientSize.width, (UINT32)clientSize.height)),
			&_d2dRenderTarget);
	}
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&_dwFactory));
	}
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&_wicImagingFactory);
	}
	bool ret = SUCCEEDED(hr);
	if (!ret)
	{
		D2D1::SafeRelease(&_wicImagingFactory);
		D2D1::SafeRelease(&_dwFactory);
		D2D1::SafeRelease(&_d2dRenderTarget);
		D2D1::SafeRelease(&_d2dFactory);
	}
	return ret;
}

void Direct2DRenderCircumstance::beginDraw()
{
	assert(_d2dRenderTarget);
	_d2dRenderTarget->BeginDraw();
	_d2dRenderTarget->Clear(D2D1::ColorF(_bgColor.r, _bgColor.g, _bgColor.b));
}

void Direct2DRenderCircumstance::endDraw()
{
	assert(_d2dRenderTarget);
	_d2dRenderTarget->EndDraw();
}

//
ID2D1Factory* Direct2DRenderCircumstance::getID2D1Factory() const { return _d2dFactory; }
ID2D1HwndRenderTarget* Direct2DRenderCircumstance::getID2D1HwndRenderTarget() const { return _d2dRenderTarget; }
IDWriteFactory* Direct2DRenderCircumstance::getIDWriteFactory() const { return _dwFactory; }
IWICImagingFactory* Direct2DRenderCircumstance::getIWICImagingFactory() const { return _wicImagingFactory; }