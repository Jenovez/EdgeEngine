// cpp文件

#include "ImageComponent.h"

USING_NS_EDGE;

ImageComponent* ImageComponent::create()
{
	auto com = new ImageComponent();
	if (com && com->init())
	{
		com->autorelease();
	}
	else
	{
		SAFE_DELETE(com);
	}
	return com;
}

ImageComponent* ImageComponent::create(const std::string& filename)
{
	auto com = new ImageComponent();
	if (com && com->init() && com->setTexture(filename))
	{
		com->autorelease();
	}
	else
	{
		SAFE_DELETE(com);
	}
	return com;
}

ImageComponent* ImageComponent::create(int cacheTag, const Data& data)
{
	auto com = new ImageComponent();
	if (com && com->init() && com->setTexture(cacheTag, data))
	{
		com->autorelease();
	}
	else
	{
		SAFE_DELETE(com);
	}
	return com;
}

ImageComponent::ImageComponent()
	: _texture2dRenderer(NULL)
	, m_fOpacity(1.0f)
	, _gameObjectTransform(NULL)
	, m_bTransformChange(false)
{
}

ImageComponent::~ImageComponent()
{
	SAFE_DELETE(_texture2dRenderer);
}

bool ImageComponent::init()
{
	if (!_texture2dRenderer)
	{
		_texture2dRenderer = _refRenderermanager->createTexture2DRenderer();
	}
	return (_texture2dRenderer != NULL);
}

bool ImageComponent::setTexture(const std::string& filename)
{
	return setTexture(_refRenderermanager->createTexture2D(filename, true));
}

bool ImageComponent::setTexture(int cacheTag, const Data& data)
{
	auto cache = _refRenderermanager->getDefaultTextureCache();
	auto texture = cache->getTexture(cacheTag);
	if (!texture)
	{
		texture = _refRenderermanager->createTexture2D(data);
		if (texture)
		{
			cache->insertTexture(cacheTag, texture);
		}
	}
	return setTexture(texture);
}

bool ImageComponent::setTexture(ITexture2D* texture)
{
	assert(texture);
	if (!texture) { return false; }
	_texture2dRenderer->setTexture(texture);
	return true;
}

void ImageComponent::setColor(const Color& color) { _texture2dRenderer->setColor(color); }
const Color& ImageComponent::getColor() const { return _texture2dRenderer->getColor(); }
void ImageComponent::setRenderRect(const Rect& rect) { _texture2dRenderer->setRenderRect(rect); }
const Rect& ImageComponent::getRenderRect() { return _texture2dRenderer->getRenderRect(); }

const Size& ImageComponent::getTextureSize() const { return _texture2dRenderer->getTexture()->getTextureSize(); }

void ImageComponent::onPositionChange(TransformComponent* transform)
{
	m_bTransformChange = true;
}

void ImageComponent::onRotationChange(TransformComponent* transform)
{
	m_bTransformChange = true;
}

void ImageComponent::onScaleChange(TransformComponent* transform)
{
	m_bTransformChange = true;
}

void ImageComponent::onTransformRelease()
{
}

void ImageComponent::onEnter()
{
	_gameObjectTransform = _gameObject->getTransformComponent();
	_gameObjectTransform->addTransformListener(this);
	m_bTransformChange = true;
}

void ImageComponent::onExit()
{
	_gameObjectTransform->removeTransformListener(this);
	_gameObjectTransform = NULL;
}

void ImageComponent::onStart()
{
}

void ImageComponent::onFastUpdate(double dt)
{
	if (_texture2dRenderer->getAnchorPoint() != _gameObject->getAnchorPoint())
	{
		m_bTransformChange = true;
	}
	if (m_bTransformChange)
	{
		_texture2dRenderer->setAnchorPoint(_gameObject->getAnchorPoint());
		_texture2dRenderer->setTransform(
			_gameObjectTransform->getPosition(),
			_gameObjectTransform->getScale(),
			_gameObjectTransform->getRotationZ());
		m_bTransformChange = false;
	}
}

void ImageComponent::onUpdate(double dt)
{
}

void ImageComponent::onLateUpdate(double dt)
{}

void ImageComponent::onRender(double dt)
{
	_texture2dRenderer->draw();
}
