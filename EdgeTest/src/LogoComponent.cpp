// cpp文件

#include "LogoComponent.h"
#include "SceneCreator.h"

USING_NS_EDGE;

LogoComponent* LogoComponent::create(Scene* runScene)
{
	auto com = new LogoComponent();
	com->autorelease();
	com->setZOrder(INT_MAX);
	com->_currentScene = runScene;
	return com;
}

LogoComponent::LogoComponent()
	: _currentScene(NULL)
	, _logo(NULL)
	, state(0)
{}

LogoComponent::~LogoComponent()
{}

void LogoComponent::onEnter()
{
	auto screenSize = _refPlatformManager->getWindow()->getClientSize();

	auto logoObj = GameObject::create();
	logoObj->setZOrder(INT_MAX);
	_logo = ImageComponent::create("res/edge_logo.png");
	logoObj->addComponent(_logo);
	logoObj->getTransformComponent()->setPosition(screenSize / 2.0);
	_currentScene->addGameObject(logoObj);

	_logo->setColor(Color(1, 1, 1, 0));
	_gameObject->addGameObject(ObjectFactory::createAudioObject("res/test.mp3"));
}

void LogoComponent::onExit()
{}

void LogoComponent::onStart()
{
}

void LogoComponent::onFastUpdate(double dt)
{
}

void LogoComponent::onUpdate(double dt)
{
	if (state == 0)
	{
		float opacity = _logo->getColor().a;
		if (opacity < 1.0f)
		{
			opacity += dt / 1.5;
			if (opacity > 1.0f)
			{
				state = 1;
				opacity = 1.0f;
			}
			_logo->setColor(Color(1, 1, 1, opacity));
		}
	}
	else if (state == 1)
	{
		float opacity = _logo->getColor().a;
		if (opacity > 0)
		{
			opacity -= dt / 1.5;
			if (opacity < 0)
			{
				state = 2;
				opacity = 0;
			}
			_logo->setColor(Color(1, 1, 1, opacity));
		}
	}
}

void LogoComponent::onLateUpdate(double dt)
{}

void LogoComponent::onRender(double dt)
{}
