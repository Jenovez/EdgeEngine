/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_TEXTURE2D_H_H__
#define __I_TEXTURE2D_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>

NS_EDGE_BEGIN

class EDGE_DLL ITexture2D
{
public:
	virtual ~ITexture2D() {}

	virtual bool initWithSize(const Size& size) = 0;
	virtual bool initWithFile(const std::string& filename) = 0;
	virtual bool initWithStream(const Data& data) = 0;

	virtual const Size& getTextureSize() const = 0;

	virtual bool isCache() const = 0;
};

NS_EDGE_END

#endif // __I_TEXTURE2D_H_H__