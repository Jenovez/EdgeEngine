// cpp文件

#include "Component.h"
#include <objects/GameObject.h>

USING_NS_EDGE;

Component::Component()
	: m_iZOrder(0)
	, _gameObject(NULL)
	, _refDirector(Director::getInstance())
	, _refAudioManager(AudioManager::getInstance())
	, _refRenderermanager(RendererManager::getInstance())
	, _refPlatformManager(PlatformManager::getInstance())
	, m_bStart(false)
{}

Component::~Component()
{}

void Component::setZOrder(int order)
{
	if (m_iZOrder != order)
	{
		m_iZOrder = order;
		if (_gameObject)
		{
			_gameObject->setSortComponentsEnable(true);
		}
	}
}
int Component::getZOrder() const { return m_iZOrder; }
Director* Component::getDirector() const { return _refDirector; }
AudioManager* Component::getAudioManager() const { return _refAudioManager; }
RendererManager* Component::getRendererManager() const { return _refRenderermanager; }
PlatformManager* Component::getPlatformManager() const { return _refPlatformManager; }