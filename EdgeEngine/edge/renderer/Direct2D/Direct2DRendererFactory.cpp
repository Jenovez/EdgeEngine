// cpp文件

#include "Direct2DRendererFactory.h"

#include "Direct2DRenderCircumstance.h"
#include "Direct2DTexture2DRenderer.h"
#include "Direct2DTexture2D.h"
#include "Direct2DTextureCache.h"
#include "Direct2DGeometryGraphics.h"
#include "Direct2DCanvasContainer.h"
#include "Direct2DFontRenderer.h"

USING_NS_EDGE;

IRenderCircumstance* Direct2DRendererFactory::createRenderCircumstance()
{
	return new Direct2DRenderCircumstance();
}

ICanvasContainer* Direct2DRendererFactory::createCanvasContainer(IRenderCircumstance* circumstance)
{
	Direct2DCanvasContainer* canvas = new Direct2DCanvasContainer((Direct2DRenderCircumstance*)circumstance);
	return canvas;
}

IGeometryGraphics* Direct2DRendererFactory::createGeometryGraphics(ICanvasContainer* canvas)
{
	Direct2DGeometryGraphics* geometryGraphics = new Direct2DGeometryGraphics(
		((Direct2DCanvasContainer*)canvas)->getID2D1BitmapRenderTarget());
	return geometryGraphics;
}

IGeometryGraphics* Direct2DRendererFactory::createGeometryGraphics(IRenderCircumstance* circumstance)
{
	Direct2DGeometryGraphics* geometryGraphics = new Direct2DGeometryGraphics(
		((Direct2DRenderCircumstance*)circumstance)->getID2D1HwndRenderTarget());
	return geometryGraphics;
}

ITexture2DRenderer* Direct2DRendererFactory::createTexture2DRenderer(ICanvasContainer* canvas)
{
	Direct2DTexture2DRenderer* renderer = new Direct2DTexture2DRenderer(
		((Direct2DCanvasContainer*)canvas)->getID2D1BitmapRenderTarget());
	return renderer;
}

ITexture2DRenderer* Direct2DRendererFactory::createTexture2DRenderer(IRenderCircumstance* circumstance)
{
	Direct2DTexture2DRenderer* renderer = new Direct2DTexture2DRenderer(
		((Direct2DRenderCircumstance*)circumstance)->getID2D1HwndRenderTarget());
	return renderer;
}

IFontRenderer* Direct2DRendererFactory::createFontRenderer(ICanvasContainer* canvas)
{
	Direct2DCanvasContainer* canc = (Direct2DCanvasContainer*)canvas;
	Direct2DFontRenderer* fontRenderer = new Direct2DFontRenderer(
		canc->getRenderCircumstance()->getIDWriteFactory(),
		canc->getID2D1BitmapRenderTarget());
	if (fontRenderer)
	{
		fontRenderer->init();
	}
	return fontRenderer;
}

IFontRenderer* Direct2DRendererFactory::createFontRenderer(IRenderCircumstance* circumstance)
{
	Direct2DFontRenderer* fontRenderer = new Direct2DFontRenderer(
		((Direct2DRenderCircumstance*)circumstance)->getIDWriteFactory(),
		((Direct2DRenderCircumstance*)circumstance)->getID2D1HwndRenderTarget());
	if (fontRenderer)
	{
		fontRenderer->init();
	}
	return fontRenderer;
}

ITexture2D* Direct2DRendererFactory::createTexture2D(IRenderCircumstance* circumstance)
{
	Direct2DTexture2D* texture = new Direct2DTexture2D((Direct2DRenderCircumstance*)circumstance);
	return texture;
}

ITextureCache* Direct2DRendererFactory::createTextureCache()
{
	Direct2DTextureCache* cache = new Direct2DTextureCache();
	return cache;
}
