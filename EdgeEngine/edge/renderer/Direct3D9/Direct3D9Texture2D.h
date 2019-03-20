/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT3D9_TEXTURE2D_H_H__
#define __DIRECT3D9_TEXTURE2D_H_H__

#include "libd3d9.h"
#include <renderer/ITexture2D.h>
#include "Direct3D9RenderCircumstance.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct3D9Texture2D final : public ITexture2D
{
	friend class Direct3D9TextureCache;

public:
	Direct3D9Texture2D(Direct3D9RenderCircumstance* renderCircumstance);
	~Direct3D9Texture2D();

	bool initWithSize(const Size& size);
	bool initWithFile(const std::string& filename);
	bool initWithStream(const Data& data);
	const Size& getTextureSize() const;

	bool isCache() const;

public:
	IDirect3DTexture9* getDirect3DTexture9() const;

private:
	IDirect3DDevice9* _device;

private:
	IDirect3DTexture9 * m_pTexture;

	Size _textureSize;
	bool m_bCache;
};

NS_EDGE_END

#endif // __DIRECT2D_TEXTURE2D_H_H__