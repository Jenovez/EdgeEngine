/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT2D_GEOMETRY_GRAPHICS_H_H__
#define __DIRECT2D_GEOMETRY_GRAPHICS_H_H__

#include <renderer/IGeometryGraphics.h>
#include "Direct2DRenderCircumstance.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct2DGeometryGraphics final : public IGeometryGraphics
{
public:
	Direct2DGeometryGraphics(ID2D1RenderTarget* renderTarget);
	~Direct2DGeometryGraphics();
	
	void drawPoint(const Vec2& pos, const Color& color = Color::WHITE, float size = 1.0f);
	void drawLine(const Vec2& startPos, const Vec2& endPos, const Color& color = Color::WHITE, float size = 1.0f);
	void drawRectangle(const Rect& rect, const Color& color = Color::WHITE, float size = 1.0f, float angle = 0, const Vec2& rotationCenterPoint = Vec2(0.5, 0.5));
	void drawFillRectangle(const Rect& rect, const Color& color = Color::WHITE, float angle = 0, const Vec2& rotationCenterPoint = Vec2(0.5, 0.5));
	void drawCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color = Color::WHITE, float size = 1.0f);
	void drawFillCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color = Color::WHITE);

private:
	ID2D1RenderTarget* _d2dRenderTarget;

	ID2D1SolidColorBrush* _d2dSolidColorBrush;
};

NS_EDGE_END

#endif // __DIRECT2D_GEOMETRY_GRAPHICS_H_H__