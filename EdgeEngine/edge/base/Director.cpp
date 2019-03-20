// cpp文件

#include "Director.h"
#include "PoolManager.h"
#include "AutoReleasePool.h"

USING_NS_EDGE;

Director* Director::getInstance()
{
	static Director _ins;
	return &_ins;
}

Director::Director()
: _application(NULL)
, _audioManager(NULL)
, _rendererManager(NULL)
, _platformManager(NULL)
, _runningScene(NULL)
{}

Director::~Director()
{}

void Director::onFastUpdate(double dt)
{
	if (!_runningScene) { return; }
	_runningScene->updateFastSchedule(dt);
}

void Director::onUpdate(double dt)
{
	PoolManager::update();
	if (!_runningScene) { return; }
	_runningScene->updateNormalSchedule(dt);
}

void Director::onLateUpdate(double dt)
{
	if (!_runningScene) { return; }
	_runningScene->updateLateSchedule(dt);
}

void Director::onRender(double dt)
{
	if (!_runningScene) { return; }
	_runningScene->updateRenderSchedule(dt);
}

void Director::runScene(Scene* scene)
{
	if (_runningScene)
	{
		_runningScene->onExit();
		_runningScene->release();
	}
	_runningScene = scene;
	if (_runningScene)
	{
		_runningScene->retain();
		_runningScene->onEnter();
	}
}

void Director::shutDown()
{
	runScene(NULL);
	PoolManager::update();
}

Scene* Director::getScene() const { return _runningScene; }

void Director::locatorApplication(Application* application) { _application = application; }
Application* Director::getApplication() const { return _application; }

void Director::locatorAudioManager(AudioManager* mgr) { _audioManager = mgr; }
AudioManager* Director::getAudioManager() const { return _audioManager; }

void Director::locatorRendererManager(RendererManager* mgr) { _rendererManager = mgr; }
RendererManager* Director::getRendererManager() const { return _rendererManager; }

void Director::locatorPlatformManager(PlatformManager* mgr) { _platformManager = mgr; }
PlatformManager* Director::getPlatformManager() const { return _platformManager; }