// cpp文件

#include "Direct3D9Texture2DRenderer.h"

USING_NS_EDGE;

Direct3D9Texture2DRenderer::Direct3D9Texture2DRenderer(Direct3D9RenderCircumstance* renderCircumstance)
: _texture(NULL)
, _device(NULL)
, _d3dTexture(NULL)
, _anchorPoint()
, _color()
, _transform()
, _renderRect()
, _position()
, _scale(Vec2(1, 1))
, m_fRotationZAngle(0)
, _transformStyle(TransformStyle::S2R2T)
{
	assert(renderCircumstance);
	_device = renderCircumstance->getDirect3DDevice9();
	assert(_device);
	// 创建顶点缓存,目标是两个三角形拼成的四边形
	HRESULT hr = _device->CreateVertexBuffer(4 * sizeof(TEXTURE_CUSTOMVERTEX), 0,
		TEXTURE_CUSTOMVERTEX::D3DFVF_TEXTURE2D,
		D3DPOOL_DEFAULT, &_pVertexBuffer, NULL);
	assert(SUCCEEDED(hr));
	// 创建索引缓存
	hr = _device->CreateIndexBuffer(6 * sizeof(WORD), 0,
		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &_pIndexBuffer, NULL);
	assert(SUCCEEDED(hr));

	WORD index[] = {
		0, 1, 2,
		0, 2, 3
	};

	WORD* pIndex = 0;
	_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	memcpy(pIndex, index, sizeof(index));
	_pIndexBuffer->Unlock();
}

Direct3D9Texture2DRenderer::~Direct3D9Texture2DRenderer()
{
	if (_texture)
	{
		if (!_texture->isCache())
		{
			delete _texture;
		}
	}
	D3D9::SafeRelease(&_pIndexBuffer);
	D3D9::SafeRelease(&_pVertexBuffer);
}

void Direct3D9Texture2DRenderer::setTexture(ITexture2D* texture)
{
	if (!texture) { return; }
	Direct3D9Texture2D* temp = dynamic_cast<Direct3D9Texture2D*>(texture);
	if (!temp) { return; }
	_texture = temp;
	_d3dTexture = _texture->getDirect3DTexture9();
	auto textureSize = _texture->getTextureSize();
	setRenderRect(Rect(0, 0, _texture->getTextureSize().width, _texture->getTextureSize().height));
	//_renderRect.setValue(0, 0, _texture->getTextureSize().width, _texture->getTextureSize().height);
	setColor(Color::WHITE);
	setTransform(_position, _scale, m_fRotationZAngle);
}
ITexture2D* Direct3D9Texture2DRenderer::getTexture() const { return _texture; }

void Direct3D9Texture2DRenderer::setAnchorPoint(const Vec2& anchor)
{
	_anchorPoint = anchor;
	setTransform(_position, _scale, m_fRotationZAngle);
}
const Vec2& Direct3D9Texture2DRenderer::getAnchorPoint() const { return _anchorPoint; }

void Direct3D9Texture2DRenderer::setColor(const Color& color)
{
	_color = color;
	for (int i = 0; i < 4; ++i)
	{
		_vertex[i]._color = D3DCOLOR_COLORVALUE(
			color.r, color.g, color.b, color.a);
	}
	void* pVertex = 0;
	_pVertexBuffer->Lock(0, sizeof(_vertex), (void**)&pVertex, 0);
	memcpy(pVertex, _vertex, sizeof(_vertex));
	_pVertexBuffer->Unlock();
}
const Color& Direct3D9Texture2DRenderer::getColor() const { return _color; }

void Direct3D9Texture2DRenderer::setTransformStyle(TransformStyle style) { _transformStyle = style; }
void Direct3D9Texture2DRenderer::setTransform(const Vec2& position, const Vec2& scale, float rotationZAngle)
{
	_position = position;
	_scale = scale;
	m_fRotationZAngle = rotationZAngle;

	D3DXMATRIX matAnchor;
	D3DXMatrixTranslation(
		&matAnchor,
		(0.5f - (FLOAT)_anchorPoint.x) * (FLOAT)(_renderRect.right - _renderRect.left),
		(0.5f - (FLOAT)_anchorPoint.y) * (FLOAT)(_renderRect.bottom - _renderRect.top),
		0);

	D3DXMATRIX matRz;
	D3DXMatrixRotationZ(&matRz, m_fRotationZAngle / 180.0f * D3DX_PI);

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, (FLOAT)scale.x, (FLOAT)scale.y, 1.0f);

	D3DXMATRIX matPos;
	D3DXMatrixTranslation(&matPos, (FLOAT)_position.x, (FLOAT)_position.y, 0);

	switch (_transformStyle)
	{
	case edge::TransformStyle::S2R2T:
		_transform = matAnchor * matScale * matRz *  matPos;
		break;
	case edge::TransformStyle::S2T2R:
		_transform = matAnchor * matScale *  matPos * matRz;
		break;
	case edge::TransformStyle::R2S2T:
		_transform = matAnchor * matRz * matScale * matPos;
		break;
	case edge::TransformStyle::R2T2S:
		_transform = matAnchor * matRz * matPos * matScale;
		break;
	case edge::TransformStyle::T2R2S:
		_transform = matAnchor * matPos * matRz * matScale;
		break;
	case edge::TransformStyle::T2S2R:
		_transform = matAnchor * matPos * matScale * matRz;
		break;
	default:
		_transform = matAnchor * matScale * matRz *  matPos;
		break;
	}
}

const Vec2& Direct3D9Texture2DRenderer::getPosition() const { return _position; }
const Vec2& Direct3D9Texture2DRenderer::getScale() const { return _scale; }
float Direct3D9Texture2DRenderer::getRotationZ() const { return m_fRotationZAngle; }

void Direct3D9Texture2DRenderer::setRenderRect(const Rect& rect)
{
	Size texSize = _texture->getTextureSize();
	_renderRect = rect;
	_renderRect.left = _renderRect.left < 0 ? 0 : _renderRect.left;
	_renderRect.top = _renderRect.top < 0 ? 0 : _renderRect.top;
	_renderRect.right = _renderRect.right > texSize.width ? texSize.width : _renderRect.right;
	_renderRect.bottom = _renderRect.bottom > texSize.height ? texSize.height : _renderRect.bottom;
	setTransform(_position, _scale, m_fRotationZAngle);

	_vertex[0]._u = (FLOAT)_renderRect.left / (FLOAT)(texSize.width);
	_vertex[0]._v = (FLOAT)_renderRect.top / (FLOAT)(texSize.height);
	_vertex[1]._u = (FLOAT)_renderRect.right / (FLOAT)(texSize.width);
	_vertex[1]._v = (FLOAT)_renderRect.top / (FLOAT)(texSize.height);
	_vertex[2]._u = (FLOAT)_renderRect.right / (FLOAT)(texSize.width);
	_vertex[2]._v = (FLOAT)_renderRect.bottom / (FLOAT)(texSize.height);
	_vertex[3]._u = (FLOAT)_renderRect.left / (FLOAT)(texSize.width);
	_vertex[3]._v = (FLOAT)_renderRect.bottom / (FLOAT)(texSize.height);

	for (int i = 0; i < 4; ++i)
	{
		if (_vertex[i]._u < 0)
		{
			_vertex[i]._u = 0;
		}
		if (_vertex[i]._u > 1)
		{
			_vertex[i]._u = 1;
		}
		if (_vertex[i]._v < 0)
		{
			_vertex[i]._v = 0;
		}
		if (_vertex[i]._v > 1)
		{
			_vertex[i]._v = 1;
		}
	}

	FLOAT width = (FLOAT)(_renderRect.right - _renderRect.left);
	FLOAT height = (FLOAT)(_renderRect.bottom - _renderRect.top);

	// 左上角
	_vertex[0]._position = D3DXVECTOR3(-width / 2.0f, -height / 2.0f, 0);
	// 右上角
	_vertex[1]._position = D3DXVECTOR3(width / 2.0f, -height / 2.0f, 0);
	// 右下角
	_vertex[2]._position = D3DXVECTOR3(width / 2.0f, height / 2.0f, 0);
	// 左下角
	_vertex[3]._position = D3DXVECTOR3(-width / 2.0f, height / 2.0f, 0);

	void* pVertex = 0;
	_pVertexBuffer->Lock(0, sizeof(_vertex), (void**)&pVertex, 0);
	memcpy(pVertex, _vertex, sizeof(_vertex));
	_pVertexBuffer->Unlock();
}
const Rect& Direct3D9Texture2DRenderer::getRenderRect() const { return _renderRect; }

void Direct3D9Texture2DRenderer::draw()
{
	if (!_d3dTexture) { return; }
	_device->SetTransform(D3DTS_WORLD, &_transform);
	_device->SetStreamSource(0, _pVertexBuffer, 0, sizeof(TEXTURE_CUSTOMVERTEX));
	_device->SetFVF(TEXTURE_CUSTOMVERTEX::D3DFVF_TEXTURE2D);
	_device->SetIndices(_pIndexBuffer);
	_device->SetTexture(0, _d3dTexture);
	_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	_device->SetTexture(0, NULL);
}