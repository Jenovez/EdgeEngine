/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT3D9_TEXTURE2D_RENDERER_H_H__
#define __DIRECT3D9_TEXTURE2D_RENDERER_H_H__

#include <renderer/ITexture2DRenderer.h>
#include "Direct3D9Texture2D.h"

NS_EDGE_BEGIN

struct EDGE_DLL TEXTURE_CUSTOMVERTEX
{
	D3DXVECTOR3 _position;
	DWORD _color;
	FLOAT _u, _v;

	static const DWORD D3DFVF_TEXTURE2D =
		D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
};

class EDGE_DLL Direct3D9Texture2DRenderer final : public ITexture2DRenderer
{
public:
	Direct3D9Texture2DRenderer(Direct3D9RenderCircumstance* renderCircumstance);
	~Direct3D9Texture2DRenderer();

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
	Direct3D9Texture2D* _texture;
	IDirect3DDevice9* _device;
	IDirect3DTexture9 * _d3dTexture;

	TEXTURE_CUSTOMVERTEX _vertex[4];
	LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;

	D3DXMATRIX _transform;

	Vec2 _anchorPoint;
	Color _color;
	Rect _renderRect;
	Vec2 _position;
	Vec2 _scale;
	float m_fRotationZAngle;
	TransformStyle _transformStyle;
};

NS_EDGE_END

#endif // __DIRECT3D9_TEXTURE2D_RENDERER_H_H__