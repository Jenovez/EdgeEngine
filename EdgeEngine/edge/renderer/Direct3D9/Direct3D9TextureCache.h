/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT3D9_TEXTURE_CACHE_H_H__
#define __DIRECT3D9_TEXTURE_CACHE_H_H__

#include <renderer/ITextureCache.h>
#include "Direct3D9Texture2D.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct3D9TextureCache final : public ITextureCache
{
public:
	Direct3D9TextureCache();
	~Direct3D9TextureCache();

	void insertTexture(const std::string& tagName, ITexture2D* texture);
	void insertTexture(int tag, ITexture2D* texture);

	void removeTexture(const std::string& tagName);
	void removeTexture(int tag);

	ITexture2D* getTexture(const std::string& tagName) const;
	ITexture2D* getTexture(int tag) const;

	void clear();

private:
	std::map<std::string, Direct3D9Texture2D*> _textureStrKeyPool;
	std::map<int, Direct3D9Texture2D*> _textureNumKeyPool;
};

NS_EDGE_END

#endif // __DIRECT3D9_TEXTURE_CACHE_H_H__