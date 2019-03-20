// cpp文件

#include "Direct3D9GeometryGraphics.h"

USING_NS_EDGE;

Direct3D9GeometryGraphics::Direct3D9GeometryGraphics(Direct3D9RenderCircumstance* renderCircumstance)
: _device(NULL)
{
	assert(renderCircumstance);
	_device = renderCircumstance->getDirect3DDevice9();
	assert(_device);

	HRESULT hr = NULL;

	// init point
	{
		hr = _device->CreateVertexBuffer(sizeof(POINT_CUSTOMVERTEX), 0,
			POINT_CUSTOMVERTEX::D3DFVF_POINT,
			D3DPOOL_DEFAULT, &_pointVertexBuffer, NULL);
		assert(SUCCEEDED(hr));
		_pointVertex._position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_pointVertex._color = 0xffffffff;
		void* pVertex = 0;
		_pointVertexBuffer->Lock(0, sizeof(_pointVertex), (void**)&pVertex, 0);
		memcpy(pVertex, &_pointVertex, sizeof(_pointVertex));
		_pointVertexBuffer->Unlock();
	}

	// init line
	{
		hr = D3DXCreateLine(_device, &_d3dLine);
		assert(SUCCEEDED(hr));
	}

	// init rectangle
	{
		hr = _device->CreateVertexBuffer(sizeof(RECTANGLE_CUSTOMVERTEX), 0,
			RECTANGLE_CUSTOMVERTEX::D3DFVF_RECTANGLE,
			D3DPOOL_DEFAULT, &_rectangleVertexBuffer, NULL);
		assert(SUCCEEDED(hr));
		_rectangleVertex[0]._position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rectangleVertex[1]._position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rectangleVertex[2]._position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rectangleVertex[3]._position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rectangleVertex[0]._color = 0xffffffff;
		_rectangleVertex[1]._color = 0xffffffff;
		_rectangleVertex[2]._color = 0xffffffff;
		_rectangleVertex[3]._color = 0xffffffff;
		void* pVertex = 0;
		_rectangleVertexBuffer->Lock(0, sizeof(_rectangleVertex), (void**)&pVertex, 0);
		memcpy(pVertex, &_rectangleVertex, sizeof(_rectangleVertex));
		_rectangleVertexBuffer->Unlock();
	}
}

Direct3D9GeometryGraphics::~Direct3D9GeometryGraphics()
{
	D3D9::SafeRelease(&_pointVertexBuffer);
	D3D9::SafeRelease(&_d3dLine);
}

void Direct3D9GeometryGraphics::drawPoint(const Vec2& pos, const Color& color, float size)
{
	DWORD tempColor = D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a);
	if (_pointVertex._color != tempColor)
	{
		_pointVertex._color = tempColor;

		void* pVertex = 0;
		_pointVertexBuffer->Lock(0, sizeof(_pointVertex), (void**)&pVertex, 0);
		memcpy(pVertex, &_pointVertex, sizeof(_pointVertex));
		_pointVertexBuffer->Unlock();
	}

	D3DXMATRIX matPos;
	D3DXMatrixTranslation(&matPos, (FLOAT)pos.x, (FLOAT)pos.y, 0);

	_device->SetTransform(D3DTS_WORLD, &matPos);

	_device->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	_device->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&size));
	_device->SetStreamSource(0, _pointVertexBuffer, 0, sizeof(POINT_CUSTOMVERTEX));
	_device->SetFVF(POINT_CUSTOMVERTEX::D3DFVF_POINT);
	_device->DrawPrimitive(D3DPT_POINTLIST, 0, 1);
	_device->SetRenderState(D3DRS_POINTSIZE, 1);
}

void Direct3D9GeometryGraphics::drawLine(const Vec2& startPos, const Vec2& endPos, const Color& color, float size)
{
	_lineVec[0].x = (FLOAT)startPos.x;
	_lineVec[0].y = (FLOAT)startPos.y;
	_lineVec[1].x = (FLOAT)endPos.x;
	_lineVec[1].y = (FLOAT)endPos.y;

	_d3dLine->SetWidth(size);
	// 开启抗锯齿
	_d3dLine->SetAntialias(TRUE);
	_d3dLine->Draw(_lineVec, 2, D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a));
}

void Direct3D9GeometryGraphics::drawRectangle(const Rect& rect, const Color& color, float size, float angle, const Vec2& rotationCenterPoint)
{
}

void Direct3D9GeometryGraphics::drawFillRectangle(const Rect& rect, const Color& color, float angle, const Vec2& rotationCenterPoint)
{

}

void Direct3D9GeometryGraphics::drawCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color, float size)
{

}

void Direct3D9GeometryGraphics::drawFillCircle(const Vec2& centerPos, float radiusX, float radiusY, const Color& color)
{

}