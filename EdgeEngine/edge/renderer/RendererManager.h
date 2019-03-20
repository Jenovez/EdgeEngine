/********************************************
名称:
说明:
1.
********************************************/

#ifndef __RENDERER_MANAGER_H_H__
#define __RENDERER_MANAGER_H_H__

#include <base/IManagerProtocol.h>
#include "RendererConfig.h"

#include "ICanvasContainer.h"
#include "IFontRenderer.h"
#include "IGeometryGraphics.h"
#include "IRenderCircumstance.h"
#include "IRendererFactory.h"
#include "ITexture2D.h"
#include "ITexture2DRenderer.h"
#include "ITextureCache.h"

NS_EDGE_BEGIN

class EDGE_DLL RendererManager final : public IManagerProtocol
{
public:
	static RendererManager* getInstance();

	bool loadConfig();
	void saveConfig();
	void resetConfig();

	bool startUp();
	bool shutDown();

	void beginUpdate();
	void update();
	void endUpdate();

	bool isStop();

public:
	ICanvasContainer* createCanvasContainer(const Size& size);
	IGeometryGraphics* createGeometryGraphics(ICanvasContainer* canvas);
	IGeometryGraphics* createGeometryGraphics();

	ITexture2DRenderer* createTexture2DRenderer(ICanvasContainer* canvas);
	ITexture2DRenderer* createTexture2DRenderer();

	IFontRenderer* createFontRenderer(ICanvasContainer* canvas);
	IFontRenderer* createFontRenderer();

	ITexture2D* createTexture2D(const std::string& filename, bool bCache = true);
	ITexture2D* createTexture2D(const Data& data);
	ITexture2D* createTexture2D(const Size& size);

public:
	IRenderCircumstance* getRenderCircumstance() const;
	ITextureCache* getDefaultTextureCache() const;

private:
	RendererManager();
	~RendererManager();
	RendererManager(const RendererManager&);
	RendererManager& operator=(const RendererManager&);

private:
	IRendererFactory* _rendererFactory;
	IRenderCircumstance* _renderCircumstance;
	ITextureCache* _defaultTextureCache;

private:
	RENDERER_TYPE _rendererType;
	Color _bgColor;
};

NS_EDGE_END

#endif // __RENDERER_MANAGER_H_H__