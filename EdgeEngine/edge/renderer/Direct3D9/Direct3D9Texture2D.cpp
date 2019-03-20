// cpp文件

#include "Direct3D9Texture2D.h"
#include "Direct3D9RenderCircumstance.h"

USING_NS_EDGE;

Direct3D9Texture2D::Direct3D9Texture2D(Direct3D9RenderCircumstance* renderCircumstance)
: _device(NULL)
, m_pTexture(NULL)
, _textureSize()
, m_bCache(false)
{
	assert(renderCircumstance);
	_device = renderCircumstance->getDirect3DDevice9();
	assert(_device);
}

Direct3D9Texture2D::~Direct3D9Texture2D()
{
	D3D9::SafeRelease(&m_pTexture);
}

bool Direct3D9Texture2D::initWithSize(const Size& size)
{
	if (size.width <= 0 || size.height <= 0) { return false; }
	HRESULT hr = D3DXCreateTexture(
		_device,
		(UInt)size.width,
		(UInt)size.height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		&m_pTexture);

	if (SUCCEEDED(hr))
	{
		_textureSize.setValue((UInt)size.width, (UInt)size.height);
	}

	return SUCCEEDED(hr);
}

bool Direct3D9Texture2D::initWithFile(const std::string& filename)
{
	if (filename.empty()) { return false; }

	D3DXIMAGE_INFO d3dxImageInfo;
	HRESULT hr = D3DXCreateTextureFromFileEx(
		_device,
		filename.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_RGBA(0, 0, 0, 1),
		&d3dxImageInfo,
		NULL,
		&m_pTexture);
	if (SUCCEEDED(hr))
	{
		_textureSize.setValue(d3dxImageInfo.Width, d3dxImageInfo.Height);
	}

	return SUCCEEDED(hr);
}

bool Direct3D9Texture2D::initWithStream(const Data& data)
{
	if (data.size == 0) { return false; }
	if (data.bin == NULL) { return false; }

	D3DXIMAGE_INFO d3dxImageInfo;
	HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(
		_device,
		data.bin,
		data.size,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_RGBA(0, 0, 0, 1),
		&d3dxImageInfo,
		NULL,
		&m_pTexture);

	if (SUCCEEDED(hr))
	{
		_textureSize.setValue(d3dxImageInfo.Width, d3dxImageInfo.Height);
	}
	return SUCCEEDED(hr);
}

const Size& Direct3D9Texture2D::getTextureSize() const { return _textureSize; }
bool Direct3D9Texture2D::isCache() const { return m_bCache; }

IDirect3DTexture9* Direct3D9Texture2D::getDirect3DTexture9() const { return m_pTexture; }