/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT2D_FONT_RENDERER_H_H__
#define __DIRECT2D_FONT_RENDERER_H_H__

#include <renderer/IFontRenderer.h>
#include "libd2d.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct2DFontRenderer final : public IFontRenderer
{
public:
	Direct2DFontRenderer(IDWriteFactory* factory, ID2D1RenderTarget* renderTarget);
	~Direct2DFontRenderer();

	bool init();

	void setString(const std::string& str);
	const std::string& getString() const;

	void setFontAttribute(float fontSize, const std::string& fontName, int fontWeight, bool italic);
	float getTextSize() const;
	const std::string& getFontName() const;
	int getFontWeight() const;
	bool isItalic() const;

	void setAnchorPoint(const Vec2& anchor);
	const Vec2& getAnchorPoint() const;

	void setColor(const Color& color);
	const Color& getColor() const;

	void setTransform(const Vec2& position, const Vec2& scale, float rotationZAngle);
	const Vec2& getPosition() const;
	const Vec2& getScale() const;
	float getRotationZ() const;

	void setMaxWidthEnable(bool e);
	bool isMaxWidthEnable() const;
	void setMaxWidth(float width);
	float getMaxWidth() const;

	const Size& getTextureSize();

	void draw();

private:
	IDWriteFactory* _dwFactory;
	ID2D1RenderTarget* _d2dRenderTarget;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pSolidColorBrush;
	WCHAR* _wcharText;
	std::string m_sText;
	std::string m_sFontName;
	float m_fFontSize;
	Color _textColor;
	D2D1::Matrix3x2F _transform;
	D2D1_RECT_F _layoutRect;
	Size _textureSize;
	Vec2 _anchorPoint;
	Vec2 _position;
	Vec2 _scale;
	float m_fRotationZAngle;
	Size _maxSize;
	int m_iWeight;
	bool m_bItalic;
	bool m_bMaxWidthEnable;
};

NS_EDGE_END

#endif // __DIRECT2D_FONT_RENDERER_H_H__