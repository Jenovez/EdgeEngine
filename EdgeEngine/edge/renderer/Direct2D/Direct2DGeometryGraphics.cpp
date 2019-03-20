// cpp文件

#include "Direct2DGeometryGraphics.h"

USING_NS_EDGE;

Direct2DGeometryGraphics::Direct2DGeometryGraphics(ID2D1RenderTarget* renderTarget)
: _d2dRenderTarget(renderTarget)
, _d2dSolidColorBrush(NULL)
{
	assert(_d2dRenderTarget);
	_d2dRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(1.0f, 1.0f, 1.0f),
		&_d2dSolidColorBrush);
	assert(_d2dSolidColorBrush);
}

Direct2DGeometryGraphics::~Direct2DGeometryGraphics()
{
	D2D1::SafeRelease(&_d2dSolidColorBrush);
}

void Direct2DGeometryGraphics::drawPoint(const Vec2& pos, const Color& color, float size)
{
	_d2dSolidColorBrush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	_d2dRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F((float)pos.x, (float)pos.y), size, size),
		_d2dSolidColorBrush);
}

void Direct2DGeometryGraphics::drawLine(const Vec2& startPos, const Vec2& endPos, const Color& color, float size)
{
	_d2dSolidColorBrush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	_d2dRenderTarget->DrawLine(
		D2D1::Point2F((float)startPos.x, (float)startPos.y),
		D2D1::Point2F((float)endPos.x, (float)endPos.y),
		_d2dSolidColorBrush, size);
}

void Direct2DGeometryGraphics::drawRectangle(const Rect& rect, const Color& color, float size, float angle, const Vec2& rotationCenterPoint)
{
	_d2dSolidColorBrush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	if (!equalsFloat(angle, 0))
	{
		D2D1_MATRIX_3X2_F transform;
		_d2dRenderTarget->GetTransform(&transform);
		D2D1_POINT_2F centerPoint = D2D1::Point2F(
			(float)(rotationCenterPoint.x * (rect.right - rect.left)),
			(float)(rotationCenterPoint.y * (rect.bottom - rect.top)));
		transform = transform * D2D1::Matrix3x2F::Rotation(angle, centerPoint);
		_d2dRenderTarget->SetTransform(transform);
		_d2dRenderTarget->DrawRectangle(
			D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
			_d2dSolidColorBrush, size);
		_d2dRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	else
	{
		_d2dRenderTarget->DrawRectangle(
			D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
			_d2dSolidColorBrush, size);
	}
}

void Direct2DGeometryGraphics::drawFillRectangle(const Rect& rect, const Color& color, float angle, const Vec2& rotationCenterPoint)
{
	_d2dSolidColorBrush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	if (!equalsFloat(angle, 0))
	{
		D2D1_MATRIX_3X2_F transform;
		_d2dRenderTarget->GetTransform(&transform);
		D2D1_POINT_2F centerPoint = D2D1::Point2F(
			(float)(rotationCenterPoint.x * (rect.right - rect.left)),
			(float)(rotationCenterPoint.y * (rect.bottom - rect.top)));
		transform = transform * D2D1::Matrix3x2F::Rotation(angle, centerPoint);
		_d2dRenderTarget->SetTransform(transform);
		_d2dRenderTarget->FillRectangle(
			D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
			_d2dSolidColorBrush);
		_d2dRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	else
	{
		_d2dRenderTarget->FillRectangle(
			D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
			_d2dSolidColorBrush);
	}
}

void Direct2DGeometryGraphics::drawCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color, float size)
{
	_d2dSolidColorBrush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	_d2dRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F((float)centerPos.x, (float)centerPos.y), radiusX, radiusY),
		_d2dSolidColorBrush, size);
}

void Direct2DGeometryGraphics::drawFillCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color)
{
	_d2dSolidColorBrush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	_d2dRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F((float)centerPos.x, (float)centerPos.y), radiusX, radiusY),
		_d2dSolidColorBrush);
}