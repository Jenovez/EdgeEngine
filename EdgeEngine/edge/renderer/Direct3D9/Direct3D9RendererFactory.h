/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT3D9_RENDERER_FACTORY_H_H__
#define __DIRECT3D9_RENDERER_FACTORY_H_H__

#include <renderer/IRendererFactory.h>

NS_EDGE_BEGIN

class EDGE_DLL Direct3D9RendererFactory final : public IRendererFactory
{
public:
	IRenderCircumstance* createRenderCircumstance();

	ICanvasContainer* createCanvasContainer(IRenderCircumstance* circumstance);

	IGeometryGraphics* createGeometryGraphics(ICanvasContainer* canvas);
	IGeometryGraphics* createGeometryGraphics(IRenderCircumstance* circumstance);

	ITexture2DRenderer* createTexture2DRenderer(ICanvasContainer* canvas);
	ITexture2DRenderer* createTexture2DRenderer(IRenderCircumstance* circumstance);
	IFontRenderer* createFontRenderer(ICanvasContainer* canvas);
	IFontRenderer* createFontRenderer(IRenderCircumstance* circumstance);

	ITexture2D* createTexture2D(IRenderCircumstance* circumstance);
	ITextureCache* createTextureCache();
};

NS_EDGE_END

#endif // __DIRECT3D9_RENDERER_FACTORY_H_H__