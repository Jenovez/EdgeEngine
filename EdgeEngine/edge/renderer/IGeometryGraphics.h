/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_GEOMETRY_GRAPHICS_H_H__
#define __I_GEOMETRY_GRAPHICS_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>

NS_EDGE_BEGIN

class EDGE_DLL IGeometryGraphics
{
public:
	virtual ~IGeometryGraphics() {}

	virtual void drawPoint(const Vec2& pos, const Color& color = Color::WHITE, float size = 1.0f) = 0;
	virtual void drawLine(const Vec2& startPos, const Vec2& endPos, const Color& color = Color::WHITE, float size = 1.0f) = 0;
	virtual void drawRectangle(const Rect& rect, const Color& color = Color::WHITE, float size = 1.0f, float angle = 0, const Vec2& rotationCenterPoint = Vec2(0.5, 0.5)) = 0;
	virtual void drawFillRectangle(const Rect& rect, const Color& color = Color::WHITE, float angle = 0, const Vec2& rotationCenterPoint = Vec2(0.5, 0.5)) = 0;
	virtual void drawCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color = Color::WHITE, float size = 1.0f) = 0;
	virtual void drawFillCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color = Color::WHITE) = 0;
};

NS_EDGE_END

#endif // __I_GEOMETRY_GRAPHICS_H_H__