/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_RENDERER_FACTORY_H_H__
#define __I_RENDERER_FACTORY_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>

NS_EDGE_BEGIN

class IRenderCircumstance;
class ICanvasContainer;
class IFontRenderer;
class IGeometryGraphics;
class ITexture2D;
class ITexture2DRenderer;
class ITextureCache;

class EDGE_DLL IRendererFactory
{
public:
	virtual ~IRendererFactory() {}

	virtual IRenderCircumstance* createRenderCircumstance() = 0;

	virtual ICanvasContainer* createCanvasContainer(IRenderCircumstance* circumstance) = 0;

	virtual IGeometryGraphics* createGeometryGraphics(ICanvasContainer* canvas) = 0;
	virtual IGeometryGraphics* createGeometryGraphics(IRenderCircumstance* circumstance) = 0;

	virtual ITexture2DRenderer* createTexture2DRenderer(ICanvasContainer* canvas) = 0;
	virtual ITexture2DRenderer* createTexture2DRenderer(IRenderCircumstance* circumstance) = 0;
	virtual IFontRenderer* createFontRenderer(ICanvasContainer* canvas) = 0;
	virtual IFontRenderer* createFontRenderer(IRenderCircumstance* circumstance) = 0;

	virtual ITexture2D* createTexture2D(IRenderCircumstance* circumstance) = 0;
	virtual ITextureCache* createTextureCache() = 0;
};

NS_EDGE_END

#endif // __I_RENDERER_FACTORY_H_H__