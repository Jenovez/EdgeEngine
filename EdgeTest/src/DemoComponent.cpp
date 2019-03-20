// cpp文件

#include "DemoComponent.h"

USING_NS_EDGE;

DemoComponent* DemoComponent::create(Scene* runScene)
{
	auto com = new DemoComponent();
	com->_currentScene = runScene;
	com->autorelease();
	return com;
}

void DemoComponent::onEnter()
{
	auto obj = ObjectFactory::createSpriteObject("res/a.jpg");
	obj->setAnchorPoint(Vec2(0.5, 0.5));
	obj->getTransformComponent()->setPosition(_refPlatformManager->getWindow()->getClientSize() / 2.0);
	_gameObject->addGameObject(obj);
}

void DemoComponent::onExit()
{}

void DemoComponent::onStart()
{
}

void DemoComponent::onFastUpdate(double dt)
{

}

void DemoComponent::onUpdate(double dt)
{}

void DemoComponent::onLateUpdate(double dt)
{
}

void DemoComponent::onRender(double dt)
{}


DemoComponent::DemoComponent()
{}

DemoComponent::~DemoComponent()
{}

