// cpp文件

#include "Direct2DTexture2D.h"
#include "Direct2DRenderCircumstance.h"

USING_NS_EDGE;

Direct2DTexture2D::Direct2DTexture2D(Direct2DRenderCircumstance* renderCircumstance)
: _renderCircumstance(renderCircumstance)
, _d2dBitmap(NULL)
, _textureSize()
, m_bCache(false)
{
	assert(renderCircumstance);
}

Direct2DTexture2D::~Direct2DTexture2D()
{
	D2D1::SafeRelease(&_d2dBitmap);
}

bool Direct2DTexture2D::initWithSize(const Size& size)
{
	if (size.width <= 0 || size.height <= 0) { return false; }
	ID2D1HwndRenderTarget* pRT = _renderCircumstance->getID2D1HwndRenderTarget();

	IWICBitmap* wicBitmap = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICImagingFactory* pWICFactory = _renderCircumstance->getIWICImagingFactory();
	HRESULT hr = pWICFactory->CreateBitmap((UINT)size.width, (UINT)size.height,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapCreateCacheOption::WICBitmapCacheOnLoad,
		&wicBitmap);
	if (SUCCEEDED(hr))
	{
		hr = pWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			wicBitmap,
			GUID_WICPixelFormat32bppPRGBA,
			WICBitmapDitherTypeNone,
			NULL,
			0.0f,
			WICBitmapPaletteTypeCustom);
	}
	if (SUCCEEDED(hr))
	{
		hr = pRT->CreateBitmapFromWicBitmap(pConverter, &_d2dBitmap);
	}

	_textureSize.setValue(size.width, size.height);

	D2D1::SafeRelease(&pConverter);
	D2D1::SafeRelease(&wicBitmap);

	bool ret = SUCCEEDED(hr);
	if (!ret)
	{
		D2D1::SafeRelease(&_d2dBitmap);
	}
	return ret;
}

bool Direct2DTexture2D::initWithFile(const std::string& filename)
{
	if (filename.empty()) { return false; }

	IWICImagingFactory* pWICFactory = _renderCircumstance->getIWICImagingFactory();
	ID2D1HwndRenderTarget* pRT = _renderCircumstance->getID2D1HwndRenderTarget();

	assert(_renderCircumstance);
	assert(pWICFactory);
	assert(pRT);

	HRESULT hr = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICFormatConverter* pConverter = NULL;

	wchar_t uriWch[256];
	MultiByteToWideChar(CP_ACP, NULL,
		filename.c_str(),
		filename.length() + 1,
		uriWch, filename.length() + 1);

	hr = pWICFactory->CreateDecoderFromFilename(
		uriWch, NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &pDecoder);

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		hr = pWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		UINT originalWidth, originalHeight;
		hr = pSource->GetSize(&originalWidth, &originalHeight);
		_textureSize.setValue(originalWidth, originalHeight);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource, // pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.0f,
			WICBitmapPaletteTypeMedianCut);
	}
	if (SUCCEEDED(hr))
	{
		hr = pRT->CreateBitmapFromWicBitmap(pConverter,
			NULL,
			&_d2dBitmap);
	}

	D2D1::SafeRelease(&pDecoder);
	D2D1::SafeRelease(&pSource);
	D2D1::SafeRelease(&pConverter);

	bool ret = SUCCEEDED(hr);
	if (!ret)
	{
		D2D1::SafeRelease(&_d2dBitmap);
	}
	return ret;
}

bool Direct2DTexture2D::initWithStream(const Data& data)
{
	if (data.size == 0) { return false; }
	if (data.bin == NULL) { return false; }

	IWICImagingFactory* pWICFactory = _renderCircumstance->getIWICImagingFactory();
	ID2D1HwndRenderTarget* pRT = _renderCircumstance->getID2D1HwndRenderTarget();

	assert(pWICFactory);
	assert(pRT);

	HRESULT hr = NULL;
	IWICStream* pStream = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = pWICFactory->CreateStream(&pStream);
	if (SUCCEEDED(hr))
	{
		hr = pStream->InitializeFromMemory(data.bin, data.size);
	}
	if (SUCCEEDED(hr))
	{
		hr = pWICFactory->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnLoad, &pDecoder);
	}
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		hr = pWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		UINT originalWidth, originalHeight;
		hr = pSource->GetSize(&originalWidth, &originalHeight);
		_textureSize.setValue(originalWidth, originalHeight);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource, // pScaler,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.0f,
			WICBitmapPaletteTypeMedianCut);
	}
	if (SUCCEEDED(hr))
	{
		hr = pRT->CreateBitmapFromWicBitmap(pConverter,
			NULL,
			&_d2dBitmap);
	}

	D2D1::SafeRelease(&pStream);
	D2D1::SafeRelease(&pDecoder);
	D2D1::SafeRelease(&pSource);
	D2D1::SafeRelease(&pConverter);

	bool ret = SUCCEEDED(hr);
	if (!ret)
	{
		D2D1::SafeRelease(&_d2dBitmap);
	}
	return ret;
}

const Size& Direct2DTexture2D::getTextureSize() const { return _textureSize; }
bool Direct2DTexture2D::isCache() const { return m_bCache; }

Direct2DRenderCircumstance* Direct2DTexture2D::getRenderCircumstance() const { return _renderCircumstance; }
ID2D1Bitmap* Direct2DTexture2D::getID2D1Bitmap() const { return _d2dBitmap; }
bool Direct2DTexture2D::initWithD2D1Bitmap(ID2D1Bitmap* bitmap)
{
	if (!bitmap) { return false; }
	_d2dBitmap = bitmap;
	auto size = _d2dBitmap->GetSize();
	_textureSize.setValue(size.width, size.height);
	return true;
}
