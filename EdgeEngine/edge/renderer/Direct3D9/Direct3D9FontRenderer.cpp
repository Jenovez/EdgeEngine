// cpp文件

#include "Direct3D9FontRenderer.h"

USING_NS_EDGE;

Direct3D9FontRenderer::Direct3D9FontRenderer(IDirect3DDevice9* device)
	: _device(device)
	, _sprite(NULL)
	, _font(NULL)
	, m_sText("")
	, m_sFontName("")
	, m_fFontSize(16)
	, _textColor(Color::WHITE)
	, _transform()
	, _textureSize()
	, _anchorPoint()
	, _position()
	, _scale(Vec2(1, 1))
	, m_fRotationZAngle(0)
	, _maxSize()
	, m_iWeight(400)
	, m_bItalic(false)
	, m_bMaxWidthEnable(false)
{
	assert(_device);

	HRESULT hr = D3DXCreateSprite(_device, &_sprite);
	assert(SUCCEEDED(hr));

	setTransform(_position, _scale, m_fRotationZAngle);
}

Direct3D9FontRenderer::~Direct3D9FontRenderer()
{
	D3D9::SafeRelease(&_font);
}

bool Direct3D9FontRenderer::init()
{
	if (m_sFontName.empty())
	{
		m_sFontName = "Consolas";
	}
	m_iWeight /= 100;
	m_iWeight *= 100;
	if (m_iWeight < 400) { m_iWeight = 400; }
	if (m_iWeight > 700) { m_iWeight = 700; }
	D3D9::SafeRelease(&_font);

	HDC hDC = GetDC(NULL);
	int nLogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);
	int nHeight = (int)(m_fFontSize * nLogPixelsY / 72);
	HRESULT hr = D3DXCreateFont(
		_device,
		nHeight,
		0,
		m_iWeight,
		1,
		m_bItalic,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		m_sFontName.c_str(),
		&_font);

	return SUCCEEDED(hr);
}

void Direct3D9FontRenderer::setString(const std::string& str)
{
	m_sText = str;

	RECT rc;
	ZeroMemory(&rc, sizeof(RECT));
	_font->DrawText(NULL,
		m_sText.c_str(),
		m_sText.length(),
		&rc,
		DT_CALCRECT,
		D3DCOLOR_COLORVALUE(_textColor.r, _textColor.g, _textColor.b, _textColor.a));

	_textureSize.width = rc.right - rc.left;
	_textureSize.height = rc.bottom - rc.top;

	if (m_bMaxWidthEnable)
	{
		_renderRect.right = rc.left + (_renderRect.right - _renderRect.left);
		_renderRect.left = rc.left;
		_renderRect.top = rc.top;
		_renderRect.bottom = rc.bottom;
	}
	else
	{
		_renderRect = rc;
	}

	setTransform(_position, _scale, m_fRotationZAngle);
}
const std::string& Direct3D9FontRenderer::getString() const { return m_sText; }
void Direct3D9FontRenderer::setFontAttribute(float fontSize, const std::string& fontName, int fontWeight, bool italic)
{
	m_fFontSize = fontSize;
	m_sFontName = fontName;
	m_iWeight = fontWeight;
	m_bItalic = italic;
	init();
}
float Direct3D9FontRenderer::getTextSize() const { return m_fFontSize; }
const std::string& Direct3D9FontRenderer::getFontName() const { return m_sFontName; }
int Direct3D9FontRenderer::getFontWeight() const { return m_iWeight; }
bool Direct3D9FontRenderer::isItalic() const { return m_bItalic; }
void Direct3D9FontRenderer::setAnchorPoint(const Vec2& anchor)
{
	_anchorPoint = anchor;
	setTransform(_position, _scale, m_fRotationZAngle);
}
const Vec2& Direct3D9FontRenderer::getAnchorPoint() const { return _anchorPoint; }
void Direct3D9FontRenderer::setColor(const Color& color)
{
	_textColor = color;
}
const Color& Direct3D9FontRenderer::getColor() const { return _textColor; }
void Direct3D9FontRenderer::setTransform(const Vec2& position, const Vec2& scale, float rotationZAngle)
{
	_position = position;
	_scale = scale;
	m_fRotationZAngle = rotationZAngle;

	D3DXMATRIX matAnchor;
	D3DXMatrixTranslation(
		&matAnchor,
		(FLOAT)(-_anchorPoint.x * _textureSize.width),
		(FLOAT)(-_anchorPoint.y * _textureSize.height),
		0);

	D3DXMATRIX matRz;
	D3DXMatrixRotationZ(&matRz, m_fRotationZAngle / 180.0f * D3DX_PI);

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, (FLOAT)scale.x, (FLOAT)scale.y, 1.0f);

	D3DXMATRIX matPos;
	D3DXMatrixTranslation(&matPos, (FLOAT)_position.x, (FLOAT)_position.y, 0);

	_transform = matAnchor * matScale * matRz *  matPos;

	_sprite->SetTransform(&_transform);
}
const Vec2& Direct3D9FontRenderer::getPosition() const { return _position; }
const Vec2& Direct3D9FontRenderer::getScale() const { return _scale; }
float Direct3D9FontRenderer::getRotationZ() const { return m_fRotationZAngle; }
void Direct3D9FontRenderer::setMaxWidthEnable(bool e) { m_bMaxWidthEnable = e; }
bool Direct3D9FontRenderer::isMaxWidthEnable() const { return m_bMaxWidthEnable; }
void Direct3D9FontRenderer::setMaxWidth(float width)
{
	if (!m_bMaxWidthEnable) { return; }
	_renderRect.right = _renderRect.left + (int)width;
}
float Direct3D9FontRenderer::getMaxWidth() const
{
	if (!m_bMaxWidthEnable) { return 0; }
	return (float)(_renderRect.right - _renderRect.left);
}
const Size& Direct3D9FontRenderer::getTextureSize() { return _textureSize; }
void Direct3D9FontRenderer::draw()
{
	_sprite->Begin(NULL);
	_font->DrawText(_sprite,
		m_sText.c_str(),
		m_sText.length(),
		&_renderRect,
		DT_LEFT | DT_TOP,
		D3DCOLOR_COLORVALUE(_textColor.r, _textColor.g, _textColor.b, _textColor.a));

	_sprite->End();
}