// cpp文件

#include "Direct2DFontRenderer.h"

USING_NS_EDGE;

Direct2DFontRenderer::Direct2DFontRenderer(IDWriteFactory* factory, ID2D1RenderTarget* renderTarget)
	: _dwFactory(factory)
	, _d2dRenderTarget(renderTarget)
	, m_pTextFormat(NULL)
	, m_pSolidColorBrush(NULL)
	, _wcharText(NULL)
	, m_sText("")
	, m_sFontName("")
	, m_fFontSize(16)
	, _textColor(Color::WHITE)
	, _transform()
	, _layoutRect()
	, _textureSize()
	, _anchorPoint()
	, _position()
	, _scale(Vec2(1, 1))
	, m_fRotationZAngle(0)
	, _maxSize()
	, m_iWeight(200)
	, m_bItalic(false)
	, m_bMaxWidthEnable(false)
{
	assert(_d2dRenderTarget);
	assert(_dwFactory);

	HRESULT hr = _d2dRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(_textColor.r, _textColor.g, _textColor.b, _textColor.a),
		&m_pSolidColorBrush);
	assert(SUCCEEDED(hr));
	setTransform(_position, _scale, m_fRotationZAngle);
}

Direct2DFontRenderer::~Direct2DFontRenderer()
{
	D2D1::SafeRelease(&m_pTextFormat);
	D2D1::SafeRelease(&m_pSolidColorBrush);
	if (_wcharText)
	{
		delete[] _wcharText;
	}
}

bool Direct2DFontRenderer::init()
{
	if (m_sFontName.empty())
	{
		m_sFontName = "Consolas";
	}
	if (m_iWeight != 350 && m_iWeight != 950)
	{
		m_iWeight /= 100;
		m_iWeight *= 100;
		if (m_iWeight < 100) { m_iWeight = 100; }
		if (m_iWeight > 950) { m_iWeight = 950; }
	}
	DWRITE_FONT_WEIGHT fontWeight = (DWRITE_FONT_WEIGHT)m_iWeight;
	DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL;
	if (m_bItalic)
	{
		fontStyle = DWRITE_FONT_STYLE_ITALIC;
	}

	D2D1::SafeRelease(&m_pTextFormat);
	wchar_t fnWch[128];
	MultiByteToWideChar(CP_ACP, NULL,
		m_sFontName.c_str(),
		m_sFontName.length() + 1,
		fnWch, m_sFontName.length() + 1);

	HRESULT hr = _dwFactory->CreateTextFormat(
		fnWch,
		NULL,
		fontWeight,
		fontStyle,
		DWRITE_FONT_STRETCH_NORMAL,
		m_fFontSize,
		L"",
		&m_pTextFormat);


	if (SUCCEEDED(hr))
	{
		hr = m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}

	return SUCCEEDED(hr);
}

void Direct2DFontRenderer::setString(const std::string& str)
{
	m_sText = str;
	if (_wcharText)
	{
		delete[] _wcharText;
	}
	_wcharText = new WCHAR[m_sText.length() + 1];
	MultiByteToWideChar(CP_ACP, NULL, m_sText.c_str(), m_sText.length() + 1, _wcharText, m_sText.length() + 1);

	// 获取文本尺寸
	IDWriteTextLayout* pTextLayout = NULL;
	_dwFactory->CreateTextLayout(
		_wcharText, m_sText.length(),
		m_pTextFormat, 0, 0, &pTextLayout);
	// 该结构体获取的是单个字体的平均大小
	DWRITE_TEXT_METRICS textMetrics;
	pTextLayout->GetMetrics(&textMetrics);
	_textureSize = Size((float)(textMetrics.width * m_sText.length()),
		(float)(textMetrics.height / (float)textMetrics.lineCount));
	D2D1::SafeRelease(&pTextLayout);


	_layoutRect.left = 0;
	_layoutRect.top = 0;
	if (!m_bMaxWidthEnable)
	{
		_layoutRect.right = (float)_textureSize.width;
	}
	_layoutRect.bottom = (float)_textureSize.height;

	setTransform(_position, _scale, m_fRotationZAngle);
}
const std::string& Direct2DFontRenderer::getString() const { return m_sText; }
void Direct2DFontRenderer::setFontAttribute(float fontSize, const std::string& fontName, int fontWeight, bool italic)
{
	m_fFontSize = fontSize;
	m_sFontName = fontName;
	m_iWeight = fontWeight;
	m_bItalic = italic;
	init();
}
float Direct2DFontRenderer::getTextSize() const { return m_fFontSize; }
const std::string& Direct2DFontRenderer::getFontName() const { return m_sFontName; }
int Direct2DFontRenderer::getFontWeight() const { return m_iWeight; }
bool Direct2DFontRenderer::isItalic() const { return m_bItalic; }
void Direct2DFontRenderer::setAnchorPoint(const Vec2& anchor)
{
	_anchorPoint = anchor;
	setTransform(_position, _scale, m_fRotationZAngle);
}
const Vec2& Direct2DFontRenderer::getAnchorPoint() const { return _anchorPoint; }
void Direct2DFontRenderer::setColor(const Color& color)
{
	_textColor = color;
	m_pSolidColorBrush->SetColor(D2D1::ColorF(_textColor.r, _textColor.g, _textColor.b, _textColor.a));
}
const Color& Direct2DFontRenderer::getColor() const { return _textColor; }
void Direct2DFontRenderer::setTransform(const Vec2& position, const Vec2& scale, float rotationZAngle)
{
	_position = position;
	_scale = scale;
	m_fRotationZAngle = rotationZAngle;

	D2D1_POINT_2F anchorPos = D2D1::Point2F(
		(float)((_layoutRect.right - _layoutRect.left) * _anchorPoint.x),
		(float)((_layoutRect.bottom - _layoutRect.top)* _anchorPoint.y));
	_d2dRenderTarget->GetTransform(&_transform);
	_transform = _transform * D2D1::Matrix3x2F::Scale((float)_scale.x, (float)_scale.y, anchorPos);
	_transform = _transform * D2D1::Matrix3x2F::Rotation((float)m_fRotationZAngle, anchorPos);
	_transform = _transform * D2D1::Matrix3x2F::Translation((float)_position.x - anchorPos.x, (float)_position.y - anchorPos.y);
}
const Vec2& Direct2DFontRenderer::getPosition() const { return _position; }
const Vec2& Direct2DFontRenderer::getScale() const { return _scale; }
float Direct2DFontRenderer::getRotationZ() const { return m_fRotationZAngle; }
void Direct2DFontRenderer::setMaxWidthEnable(bool e) { m_bMaxWidthEnable = e; }
bool Direct2DFontRenderer::isMaxWidthEnable() const { return m_bMaxWidthEnable; }
void Direct2DFontRenderer::setMaxWidth(float width)
{
	if (!m_bMaxWidthEnable) { return; }
	_layoutRect = D2D1::RectF(
		_layoutRect.left,
		_layoutRect.top,
		_layoutRect.left + (float)width,
		_layoutRect.bottom);
}
float Direct2DFontRenderer::getMaxWidth() const
{
	if (!m_bMaxWidthEnable) { return 0; }
	return _layoutRect.right - _layoutRect.left;
}
const Size& Direct2DFontRenderer::getTextureSize() { return _textureSize; }
void Direct2DFontRenderer::draw()
{
	_d2dRenderTarget->SetTransform(_transform);
	_d2dRenderTarget->DrawText(_wcharText, m_sText.length(), m_pTextFormat, _layoutRect, m_pSolidColorBrush);
	_d2dRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}