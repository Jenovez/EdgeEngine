// cpp文件

#include "Direct2DTexture2DRenderer.h"

USING_NS_EDGE;

Direct2DTexture2DRenderer::Direct2DTexture2DRenderer(ID2D1RenderTarget* rt)
	: _d2dTexture2D(NULL)
	, _d2dRenderTarget(rt)
	, _d2dBitmap(NULL)
	, _anchorPoint()
	, _color()
	, _d2dTransform(D2D1::Matrix3x2F::Identity())
	, _renderRect()
	, _position()
	, _scale(Vec2(1, 1))
	, m_fRotationZAngle(0)
	, _transformStyle(TransformStyle::S2R2T)
{
	assert(_d2dRenderTarget);
}

Direct2DTexture2DRenderer::~Direct2DTexture2DRenderer()
{
}

void Direct2DTexture2DRenderer::setTexture(ITexture2D* texture)
{
	if (!texture) { return; }
	Direct2DTexture2D* temp = dynamic_cast<Direct2DTexture2D*>(texture);
	if (!temp) { return; }
	_d2dTexture2D = temp;
	_d2dBitmap = _d2dTexture2D->getID2D1Bitmap();
	_renderRect.setValue(0, 0, _d2dTexture2D->getTextureSize().width, _d2dTexture2D->getTextureSize().height);
	setTransform(_position, _scale, m_fRotationZAngle);
}

ITexture2D* Direct2DTexture2DRenderer::getTexture() const { return _d2dTexture2D; }

void Direct2DTexture2DRenderer::setAnchorPoint(const Vec2& anchor)
{
	_anchorPoint = anchor; 
	setTransform(_position, _scale, m_fRotationZAngle);
}
const Vec2& Direct2DTexture2DRenderer::getAnchorPoint() const { return _anchorPoint; }

void Direct2DTexture2DRenderer::setColor(const Color& color) { _color = color; }
const Color& Direct2DTexture2DRenderer::getColor() const { return _color; }

void Direct2DTexture2DRenderer::setTransformStyle(TransformStyle style) { _transformStyle = style; }
void Direct2DTexture2DRenderer::setTransform(const Vec2& position, const Vec2& scale, float rotationZAngle)
{
	_position = position;
	_scale = scale;
	m_fRotationZAngle = rotationZAngle;

	D2D1_POINT_2F anchorPos = D2D1::Point2F(
		(float)((_renderRect.right - _renderRect.left) * _anchorPoint.x + _renderRect.left),
		(float)((_renderRect.bottom - _renderRect.top)* _anchorPoint.y + _renderRect.top));

	_d2dTransform = D2D1::Matrix3x2F::Identity();
	switch (_transformStyle)
	{
	case edge::TransformStyle::S2R2T:
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Scale((float)_scale.x, (float)_scale.y, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Rotation((float)m_fRotationZAngle, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Translation((float)_position.x - anchorPos.x, (float)_position.y - anchorPos.y);
		break;
	case edge::TransformStyle::S2T2R:
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Scale((float)_scale.x, (float)_scale.y, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Translation((float)_position.x - anchorPos.x, (float)_position.y - anchorPos.y);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Rotation((float)m_fRotationZAngle, anchorPos);
		break;
	case edge::TransformStyle::R2S2T:
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Rotation((float)m_fRotationZAngle, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Scale((float)_scale.x, (float)_scale.y, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Translation((float)_position.x - anchorPos.x, (float)_position.y - anchorPos.y);
		break;
	case edge::TransformStyle::R2T2S:
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Rotation((float)m_fRotationZAngle, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Translation((float)_position.x - anchorPos.x, (float)_position.y - anchorPos.y);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Scale((float)_scale.x, (float)_scale.y, anchorPos);
		break;
	case edge::TransformStyle::T2R2S:
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Translation((float)_position.x - anchorPos.x, (float)_position.y - anchorPos.y);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Rotation((float)m_fRotationZAngle, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Scale((float)_scale.x, (float)_scale.y, anchorPos);
		break;
	case edge::TransformStyle::T2S2R:
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Translation((float)_position.x - anchorPos.x, (float)_position.y - anchorPos.y);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Scale((float)_scale.x, (float)_scale.y, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Rotation((float)m_fRotationZAngle, anchorPos);
		break;
	default:
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Scale((float)_scale.x, (float)_scale.y, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Rotation((float)m_fRotationZAngle, anchorPos);
		_d2dTransform = _d2dTransform * D2D1::Matrix3x2F::Translation((float)_position.x - anchorPos.x, (float)_position.y - anchorPos.y);
		break;
	}

	D2D1::Matrix3x2F worldTransform;
	_d2dRenderTarget->GetTransform(&worldTransform);
	_d2dTransform = _d2dTransform * worldTransform;
}

const Vec2& Direct2DTexture2DRenderer::getPosition() const { return _position; }
const Vec2& Direct2DTexture2DRenderer::getScale() const { return _scale; }
float Direct2DTexture2DRenderer::getRotationZ() const { return m_fRotationZAngle; }

void Direct2DTexture2DRenderer::setRenderRect(const Rect& rect)
{
	Size texSize = _d2dTexture2D->getTextureSize();
	_renderRect = rect;
	_renderRect.left = _renderRect.left < 0 ? 0 : _renderRect.left;
	_renderRect.top = _renderRect.top < 0 ? 0 : _renderRect.top;
	_renderRect.right = _renderRect.right > texSize.width ? texSize.width : _renderRect.right;
	_renderRect.bottom = _renderRect.bottom > texSize.height ? texSize.height : _renderRect.bottom;
	setTransform(_position, _scale, m_fRotationZAngle);
}
const Rect& Direct2DTexture2DRenderer::getRenderRect() const { return _renderRect; }

void Direct2DTexture2DRenderer::draw()
{
	if (!_d2dBitmap) { return; }
	D2D1_RECT_F destinationRect = D2D1::RectF(
		(float)_renderRect.left,
		(float)_renderRect.top,
		(float)_renderRect.right,
		(float)_renderRect.bottom);

	_d2dRenderTarget->SetTransform(_d2dTransform);
	_d2dRenderTarget->DrawBitmap(_d2dBitmap,
		destinationRect,
		_color.a,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		destinationRect);

	_d2dRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}