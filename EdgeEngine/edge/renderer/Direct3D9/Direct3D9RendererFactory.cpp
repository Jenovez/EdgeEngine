// cpp文件

#include "Direct3D9RendererFactory.h"

#include "Direct3D9RenderCircumstance.h"
#include "Direct3D9Texture2DRenderer.h"
#include "Direct3D9Texture2D.h"
#include "Direct3D9TextureCache.h"
#include "Direct3D9GeometryGraphics.h"
//#include "Direct3D9CanvasContainer.h"
#include "Direct3D9FontRenderer.h"

USING_NS_EDGE;

IRenderCircumstance* Direct3D9RendererFactory::createRenderCircumstance()
{
	Direct3D9RenderCircumstance* circumstance = new Direct3D9RenderCircumstance();
	return circumstance;
}

ICanvasContainer* Direct3D9RendererFactory::createCanvasContainer(IRenderCircumstance* circumstance)
{
	return NULL;
}

IGeometryGraphics* Direct3D9RendererFactory::createGeometryGraphics(ICanvasContainer* canvas)
{
	return NULL;
}

IGeometryGraphics* Direct3D9RendererFactory::createGeometryGraphics(IRenderCircumstance* circumstance)
{
	Direct3D9GeometryGraphics* geometryGraphics = new Direct3D9GeometryGraphics(
		((Direct3D9RenderCircumstance*)circumstance));
	return geometryGraphics;
}

ITexture2DRenderer* Direct3D9RendererFactory::createTexture2DRenderer(ICanvasContainer* canvas)
{
	return NULL;
}

ITexture2DRenderer* Direct3D9RendererFactory::createTexture2DRenderer(IRenderCircumstance* circumstance)
{
	Direct3D9Texture2DRenderer* renderer = new Direct3D9Texture2DRenderer(
		((Direct3D9RenderCircumstance*)circumstance));
	return renderer;
}

IFontRenderer* Direct3D9RendererFactory::createFontRenderer(ICanvasContainer* canvas)
{
	return NULL;
}

IFontRenderer* Direct3D9RendererFactory::createFontRenderer(IRenderCircumstance* circumstance)
{
	Direct3D9FontRenderer* font = new Direct3D9FontRenderer(
		((Direct3D9RenderCircumstance*)circumstance)->getDirect3DDevice9());
	if (font)
	{
		font->init();
	}
	return font;
}

ITexture2D* Direct3D9RendererFactory::createTexture2D(IRenderCircumstance* circumstance)
{
	Direct3D9Texture2D* texture = new Direct3D9Texture2D((Direct3D9RenderCircumstance*)circumstance);
	return texture;
}

ITextureCache* Direct3D9RendererFactory::createTextureCache()
{
	Direct3D9TextureCache* cache = new Direct3D9TextureCache();
	return cache;
}
