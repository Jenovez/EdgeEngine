/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT3D9_GEOMETRY_GRAPHICS_H_H__
#define __DIRECT3D9_GEOMETRY_GRAPHICS_H_H__

#include <renderer/IGeometryGraphics.h>
#include "Direct3D9RenderCircumstance.h"

NS_EDGE_BEGIN

struct EDGE_DLL POINT_CUSTOMVERTEX
{
	D3DXVECTOR3 _position;
	DWORD _color;

	static const DWORD D3DFVF_POINT =
		D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

struct EDGE_DLL RECTANGLE_CUSTOMVERTEX
{
	D3DXVECTOR3 _position;
	DWORD _color;

	static const DWORD D3DFVF_RECTANGLE =
		D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

class EDGE_DLL Direct3D9GeometryGraphics final : public IGeometryGraphics
{
public:
	Direct3D9GeometryGraphics(Direct3D9RenderCircumstance* renderCircumstance);
	~Direct3D9GeometryGraphics();
	
	void drawPoint(const Vec2& pos, const Color& color = Color::WHITE, float size = 1.0f);
	void drawLine(const Vec2& startPos, const Vec2& endPos, const Color& color = Color::WHITE, float size = 1.0f);
	void drawRectangle(const Rect& rect, const Color& color = Color::WHITE, float size = 1.0f, float angle = 0, const Vec2& rotationCenterPoint = Vec2(0.5, 0.5));
	void drawFillRectangle(const Rect& rect, const Color& color = Color::WHITE, float angle = 0, const Vec2& rotationCenterPoint = Vec2(0.5, 0.5));
	void drawCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color = Color::WHITE, float size = 1.0f);
	void drawFillCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color = Color::WHITE);

private:
	IDirect3DDevice9* _device;

private: // point
	POINT_CUSTOMVERTEX _pointVertex;
	LPDIRECT3DVERTEXBUFFER9 _pointVertexBuffer;

private: // line
	ID3DXLine* _d3dLine;
	D3DXVECTOR2 _lineVec[2];

private:// rectangle
	RECTANGLE_CUSTOMVERTEX _rectangleVertex[4];
	LPDIRECT3DVERTEXBUFFER9 _rectangleVertexBuffer;
};

NS_EDGE_END

#endif // __DIRECT3D9_GEOMETRY_GRAPHICS_H_H__