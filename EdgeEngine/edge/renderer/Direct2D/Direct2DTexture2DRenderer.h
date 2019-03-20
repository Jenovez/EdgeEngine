/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT2D_TEXTURE2D_RENDERER_H_H__
#define __DIRECT2D_TEXTURE2D_RENDERER_H_H__

#include <renderer/ITexture2DRenderer.h>
#include "Direct2DTexture2D.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct2DTexture2DRenderer final : public ITexture2DRenderer
{
public:
	Direct2DTexture2DRenderer(ID2D1RenderTarget* rt);
	~Direct2DTexture2DRenderer();

	void setTexture(ITexture2D* texture);
	ITexture2D* getTexture() const;

	void setAnchorPoint(const Vec2& anchor);
	const Vec2& getAnchorPoint() const;

	void setColor(const Color& color);
	const Color& getColor() const;

	void setTransformStyle(TransformStyle style);
	void setTransform(const Vec2& position, const Vec2& scale, float rotationZAngle);
	const Vec2& getPosition() const;
	const Vec2& getScale() const;
	float getRotationZ() const;

	void setRenderRect(const Rect& rect);
	const Rect& getRenderRect() const;

	void draw();

private:
	Direct2DTexture2D* _d2dTexture2D;
	ID2D1RenderTarget* _d2dRenderTarget;
	ID2D1Bitmap* _d2dBitmap;
	Vec2 _anchorPoint;
	Color _color;
	D2D1::Matrix3x2F _d2dTransform;
	Rect _renderRect;
	Vec2 _position;
	Vec2 _scale;
	float m_fRotationZAngle;
	TransformStyle _transformStyle;
};

NS_EDGE_END

#endif // __DIRECT2D_TEXTURE2D_RENDERER_H_H__