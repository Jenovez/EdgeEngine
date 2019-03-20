// cpp文件

#include "ObjectFactory.h"
#include <components/ImageComponent.h>
#include <components/AudioComponent.h>

USING_NS_EDGE;

GameObject* ObjectFactory::createSpriteObject()
{
	GameObject* sprite = GameObject::create();
	sprite->addComponent(ImageComponent::create());
	return sprite;
}

GameObject* ObjectFactory::createSpriteObject(const std::string& filename)
{
	GameObject* sprite = GameObject::create();
	sprite->addComponent(ImageComponent::create(filename));
	return sprite;
}

GameObject* ObjectFactory::createSpriteObject(int cacheTag, const Data& data)
{
	GameObject* sprite = GameObject::create();
	sprite->addComponent(ImageComponent::create(cacheTag, data));
	return sprite;
}

GameObject* ObjectFactory::createAudioObject()
{
	GameObject* obj = GameObject::create();
	obj->addComponent(AudioComponent::create());
	return obj;
}

GameObject* ObjectFactory::createAudioObject(const std::string& filename)
{
	GameObject* obj = GameObject::create();
	obj->addComponent(AudioComponent::create(filename));
	return obj;
}
