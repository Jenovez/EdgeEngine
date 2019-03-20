/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_TEXTURE2D_RENDERER_H_H__
#define __I_TEXTURE2D_RENDERER_H_H__

#include "ITexture2D.h"

NS_EDGE_BEGIN

class ICanvas;

enum class TransformStyle
{
	S2R2T = 0,
	S2T2R,
	R2S2T,
	R2T2S,
	T2R2S,
	T2S2R
};

class EDGE_DLL ITexture2DRenderer
{
public:
	virtual ~ITexture2DRenderer() {}

	virtual void setTexture(ITexture2D* texture) = 0;
	virtual ITexture2D* getTexture() const = 0;

	virtual void setAnchorPoint(const Vec2& anchor) = 0;
	virtual const Vec2& getAnchorPoint() const = 0;

	virtual void setColor(const Color& color) = 0;
	virtual const Color& getColor() const = 0;

	virtual void setTransformStyle(TransformStyle style) = 0;
	virtual void setTransform(const Vec2& position, const Vec2& scale, float rotationZAngle) = 0;
	virtual const Vec2& getPosition() const = 0;
	virtual const Vec2& getScale() const = 0;
	virtual float getRotationZ() const = 0;

	virtual void setRenderRect(const Rect& rect) = 0;
	virtual const Rect& getRenderRect() const = 0;

	virtual void draw() = 0;
};

NS_EDGE_END


#endif // __I_TEXTURE2D_RENDERER_H_H__