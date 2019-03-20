/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT3D9_FONT_RENDERER_H_H__
#define __DIRECT3D9_FONT_RENDERER_H_H__

#include <renderer/IFontRenderer.h>
#include "libd3d9.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct3D9FontRenderer final : public IFontRenderer
{
public:
	Direct3D9FontRenderer(IDirect3DDevice9* device);
	~Direct3D9FontRenderer();

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
	IDirect3DDevice9* _device;
	ID3DXSprite* _sprite;
	ID3DXFont* _font;

	std::string m_sText;
	std::string m_sFontName;
	float m_fFontSize;
	Color _textColor;
	D3DXMATRIX _transform;
	RECT _renderRect;
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

#endif // __DIRECT3D9_FONT_RENDERER_H_H__