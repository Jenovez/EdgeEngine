// cpp文件

#include "RendererManager.h"

#include <rapidjson/include/document.h>
#include <rapidjson/include/writer.h>
#include <utils/FileUtils.h>
#include <platform/PlatformManager.h>

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "Direct2D/Direct2DRendererFactory.h"
#include "Direct3D9/Direct3D9RendererFactory.h"
#endif

#define RendererConfigPath "engine/renderer.config"

USING_NS_EDGE;

RendererManager* RendererManager::getInstance()
{
	static RendererManager _ins;
	return &_ins;
}

RendererManager::RendererManager()
	: _rendererFactory(NULL)
	, _renderCircumstance(NULL)
	, _defaultTextureCache(NULL)
	, _rendererType(RENDERER_TYPE::NONE)
	, _bgColor(0.2f, 0.2f, 0.2f, 1)
{}

RendererManager::~RendererManager()
{}

bool RendererManager::loadConfig()
{
	if (!FileUtils::isFileExist(RendererConfigPath)) { return false; }
	rapidjson::Document doc;
	std::string jsonStr = FileUtils::readStringFromFile(RendererConfigPath);
	doc.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());
	rapidjson::ParseErrorCode err = doc.GetParseError();
	if (doc.GetParseError() != rapidjson::ParseErrorCode::kParseErrorNone) { return false; }
	_rendererType = (RENDERER_TYPE)doc["RendererType"].GetInt();
	_bgColor.setValue(doc["BgColor"][0].GetFloat(), doc["BgColor"][1].GetFloat(), doc["BgColor"][2].GetFloat(), 1);

	return true;
}

void RendererManager::saveConfig()
{
	rapidjson::Document doc;
	doc.SetObject();
	doc.AddMember("RendererType", (int)_rendererType, doc.GetAllocator());
	rapidjson::Value bgColorValue;
	bgColorValue.SetArray();
	bgColorValue.PushBack(0, doc.GetAllocator());
	bgColorValue.PushBack(0, doc.GetAllocator());
	bgColorValue.PushBack(0, doc.GetAllocator());
	doc.AddMember("BgColor", bgColorValue, doc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	std::string jsonStr = buffer.GetString();
	jsonStr.append("\n");
	bool ret = FileUtils::writeStringToFile(RendererConfigPath, jsonStr);
	assert(ret);
}

void RendererManager::resetConfig()
{
#if TARGET_PLATFORM == PLATFORM_WIN32
	_rendererType = RENDERER_TYPE::DIRECT2D;
#else
	_rendererType = RENDERER_TYPE::OPENGL;
#endif
	_bgColor = Color(0.2f, 0.2f, 0.2f, 1);
}

bool RendererManager::startUp()
{
	SAFE_DELETE(_defaultTextureCache);
	SAFE_DELETE(_renderCircumstance);
	SAFE_DELETE(_rendererFactory);

	switch (_rendererType)
	{
	case edge::RENDERER_TYPE::OPENGL:
		break;
	case edge::RENDERER_TYPE::OPENGLES:
		break;
#if TARGET_PLATFORM == PLATFORM_WIN32
	case edge::RENDERER_TYPE::DIRECT2D:
		_rendererFactory = new Direct2DRendererFactory();
		break;
	case edge::RENDERER_TYPE::DIRECT3D9:
		_rendererFactory = new Direct3D9RendererFactory();
		break;
	case edge::RENDERER_TYPE::DIRECT3D11:
		break;
	case edge::RENDERER_TYPE::GDI:
		break;
#endif
	default: return false;
	}

	_renderCircumstance = _rendererFactory->createRenderCircumstance();
	_defaultTextureCache = _rendererFactory->createTextureCache();

	if (!_renderCircumstance->initRenderer(
		PlatformManager::getInstance()->getWindow(), _bgColor))
	{
		return false;
	}

	return true;
}

bool RendererManager::shutDown()
{
	SAFE_DELETE(_defaultTextureCache);
	SAFE_DELETE(_renderCircumstance);
	SAFE_DELETE(_rendererFactory);

	return true;
}

void RendererManager::beginUpdate()
{
	_renderCircumstance->beginDraw();
}

void RendererManager::update()
{
}

void RendererManager::endUpdate()
{
	_renderCircumstance->endDraw();
}

bool RendererManager::isStop()
{
	return false;
}

ICanvasContainer* RendererManager::createCanvasContainer(const Size& size)
{
	ICanvasContainer* canvas = _rendererFactory->createCanvasContainer(_renderCircumstance);
	if (canvas)
	{
		if (!canvas->init(size))
		{
			SAFE_DELETE(canvas);
		}
	}
	return canvas;
}

IGeometryGraphics* RendererManager::createGeometryGraphics(ICanvasContainer* canvas)
{
	return _rendererFactory->createGeometryGraphics(canvas);
}

IGeometryGraphics* RendererManager::createGeometryGraphics()
{
	return _rendererFactory->createGeometryGraphics(_renderCircumstance);
}

ITexture2DRenderer* RendererManager::createTexture2DRenderer(ICanvasContainer* canvas)
{
	return _rendererFactory->createTexture2DRenderer(canvas);
}

ITexture2DRenderer* RendererManager::createTexture2DRenderer()
{
	return _rendererFactory->createTexture2DRenderer(_renderCircumstance);
}

IFontRenderer* RendererManager::createFontRenderer(ICanvasContainer* canvas)
{
	return _rendererFactory->createFontRenderer(canvas);
}

IFontRenderer* RendererManager::createFontRenderer()
{
	return _rendererFactory->createFontRenderer(_renderCircumstance);
}

ITexture2D* RendererManager::createTexture2D(const std::string& filename, bool bCache)
{
	ITexture2D* texture = NULL;
	if (bCache)
	{
		texture = _defaultTextureCache->getTexture(filename);
		if (texture)
		{
			return texture;
		}
	}
	texture = _rendererFactory->createTexture2D(_renderCircumstance);
	if (!texture || !texture->initWithFile(filename))
	{
		SAFE_DELETE(texture);
	}
	if (texture && bCache)
	{
		_defaultTextureCache->insertTexture(filename, texture);
	}
	return texture;
}

ITexture2D* RendererManager::createTexture2D(const Data& data)
{
	ITexture2D* texture = _rendererFactory->createTexture2D(_renderCircumstance);
	if (!texture || !texture->initWithStream(data))
	{
		SAFE_DELETE(texture);
	}
	return texture;
}

ITexture2D* RendererManager::createTexture2D(const Size& size)
{
	ITexture2D* texture = _rendererFactory->createTexture2D(_renderCircumstance);
	if (!texture || !texture->initWithSize(size))
	{
		SAFE_DELETE(texture);
	}
	return texture;
}

IRenderCircumstance* RendererManager::getRenderCircumstance() const { return _renderCircumstance; }
ITextureCache* RendererManager::getDefaultTextureCache() const { return _defaultTextureCache; }
