/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_TEXTURE_CACHE_H_H__
#define __I_TEXTURE_CACHE_H_H__

#include <base/CommonConfig.h>
#include "ITexture2D.h"

NS_EDGE_BEGIN

class EDGE_DLL ITextureCache
{
public:
	virtual ~ITextureCache() {}

	virtual void insertTexture(const std::string& tagName, ITexture2D* texture) = 0;
	virtual void insertTexture(int tag, ITexture2D* texture) = 0;

	virtual void removeTexture(const std::string& tagName) = 0;
	virtual void removeTexture(int tag) = 0;

	virtual ITexture2D* getTexture(const std::string& tagName) const = 0;
	virtual ITexture2D* getTexture(int tag) const = 0;

	virtual void clear() = 0;
};

NS_EDGE_END

#endif // __I_TEXTURE_CACHE_H_H__