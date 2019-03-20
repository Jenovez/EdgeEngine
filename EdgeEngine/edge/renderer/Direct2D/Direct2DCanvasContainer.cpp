// cpp文件

#include "Direct2DCanvasContainer.h"
#include "Direct2DTexture2D.h"

USING_NS_EDGE;

Direct2DCanvasContainer::Direct2DCanvasContainer(Direct2DRenderCircumstance* circumstance)
	: _d2dRC(circumstance)
	, _renderRT(NULL)
	, _bgColor(Color::BLACK)
{
	assert(circumstance);
}

Direct2DCanvasContainer::~Direct2DCanvasContainer()
{
	SAFE_DELETE(_texture2d);
	D2D1::SafeRelease(&_renderRT);
}

bool Direct2DCanvasContainer::init(const Size& size)
{
	D2D1::SafeRelease(&_renderRT);

	HRESULT hr = NULL;
	auto pRt = _d2dRC->getID2D1HwndRenderTarget();

	hr = pRt->CreateCompatibleRenderTarget(
		D2D1::SizeF((FLOAT)size.width, (FLOAT)size.height),
		&_renderRT);

	bool ret = SUCCEEDED(hr);
	if (ret)
	{
		ID2D1Bitmap* bitmap = NULL;
		_renderRT->GetBitmap(&bitmap);
		SAFE_DELETE(_texture2d);
		_texture2d = new Direct2DTexture2D(_d2dRC);
		ret = _texture2d->initWithD2D1Bitmap(bitmap);
	}
	if (!ret)
	{
		SAFE_DELETE(_texture2d);
		D2D1::SafeRelease(&_renderRT);
	}
	return ret;
}
void Direct2DCanvasContainer::setBgColor(const Color& color) { _bgColor = color; }
const Color& Direct2DCanvasContainer::getBgColor() const { return _bgColor; }
void Direct2DCanvasContainer::beginDraw()
{
	if (!_renderRT) { return; }
	_renderRT->Clear(
		D2D1::ColorF(
			_bgColor.r,
			_bgColor.g,
			_bgColor.b,
			_bgColor.a));
	_renderRT->BeginDraw();
}

void Direct2DCanvasContainer::endDraw()
{
	if (!_renderRT) { return; }
	_renderRT->EndDraw();
}

ITexture2D* Direct2DCanvasContainer::getTexture2D() { return _texture2d; }
Direct2DRenderCircumstance* Direct2DCanvasContainer::getRenderCircumstance() const { return _d2dRC; }
ID2D1BitmapRenderTarget* Direct2DCanvasContainer::getID2D1BitmapRenderTarget() const { return _renderRT; }
