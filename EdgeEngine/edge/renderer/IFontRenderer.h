/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_FONT_RENDERER_H_H__
#define __I_FONT_RENDERER_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>

NS_EDGE_BEGIN

class EDGE_DLL IFontRenderer
{
public:
	virtual ~IFontRenderer() {}

	virtual void setString(const std::string& str) = 0;
	virtual const std::string& getString() const = 0;

	virtual void setFontAttribute(float fontSize, const std::string& fontName, int fontWeight, bool italic) = 0;
	virtual float getTextSize() const = 0;
	virtual const std::string& getFontName() const = 0;
	virtual int getFontWeight() const = 0;
	virtual bool isItalic() const = 0;

	virtual void setAnchorPoint(const Vec2& anchor) = 0;
	virtual const Vec2& getAnchorPoint() const = 0;

	virtual void setColor(const Color& color) = 0;
	virtual const Color& getColor() const = 0;

	virtual void setTransform(const Vec2& position, const Vec2& scale, float rotationZAngle) = 0;
	virtual const Vec2& getPosition() const = 0;
	virtual const Vec2& getScale() const = 0;
	virtual float getRotationZ() const = 0;

	virtual void setMaxWidthEnable(bool e) = 0;
	virtual bool isMaxWidthEnable() const = 0;
	virtual void setMaxWidth(float width) = 0;
	virtual float getMaxWidth() const = 0;

	virtual const Size& getTextureSize() = 0;

	virtual void draw() = 0;
};

NS_EDGE_END

#endif // __I_FONT_RENDERER_H_H__