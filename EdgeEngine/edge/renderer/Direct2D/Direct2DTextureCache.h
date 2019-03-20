/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT2D_TEXTURE_CACHE_H_H__
#define __DIRECT2D_TEXTURE_CACHE_H_H__

#include <renderer/ITextureCache.h>
#include "Direct2DTexture2D.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct2DTextureCache final : public ITextureCache
{
public:
	Direct2DTextureCache();
	~Direct2DTextureCache();

	void insertTexture(const std::string& tagName, ITexture2D* texture);
	void insertTexture(int tag, ITexture2D* texture);

	void removeTexture(const std::string& tagName);
	void removeTexture(int tag);

	ITexture2D* getTexture(const std::string& tagName) const;
	ITexture2D* getTexture(int tag) const;

	void clear();

private:
	std::map<std::string, Direct2DTexture2D*> _textureStrKeyPool;
	std::map<int, Direct2DTexture2D*> _textureNumKeyPool;
};

NS_EDGE_END

#endif // __DIRECT2D_TEXTURE_CACHE_H_H__