/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT2D_TEXTURE2D_H_H__
#define __DIRECT2D_TEXTURE2D_H_H__

#include "libd2d.h"
#include <renderer/ITexture2D.h>
#include "Direct2DRenderCircumstance.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct2DTexture2D final : public ITexture2D
{
	friend class Direct2DTextureCache;

public:
	Direct2DTexture2D(Direct2DRenderCircumstance* renderCircumstance);
	~Direct2DTexture2D();

	bool initWithSize(const Size& size);
	bool initWithFile(const std::string& filename);
	bool initWithStream(const Data& data);
	const Size& getTextureSize() const;

	bool isCache() const;

public:
	Direct2DRenderCircumstance* getRenderCircumstance() const;
	ID2D1Bitmap* getID2D1Bitmap() const;
	bool initWithD2D1Bitmap(ID2D1Bitmap* bitmap);

private:
	Direct2DRenderCircumstance* _renderCircumstance;

private:
	ID2D1Bitmap* _d2dBitmap;

private:
	Size _textureSize;

	bool m_bCache;
};

NS_EDGE_END

#endif // __DIRECT2D_TEXTURE2D_H_H__