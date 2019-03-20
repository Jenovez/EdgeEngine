// cpp文件

#include "SceneCreator.h"

#include "LogoComponent.h"
#include "DemoComponent.h"

USING_NS_EDGE;

Scene* SceneCreator::createLogoScene()
{
	Scene* scene = Scene::create();

	scene->addComponent(LogoComponent::create(scene));

	return scene;
}

Scene* SceneCreator::createGameRunScene()
{
	Scene* scene = Scene::create();
	scene->addGameObject(ObjectFactory::createAudioObject("res/test.mp3"));
	return scene;
}

Scene* SceneCreator::createFinishScene()
{
	Scene* scene = Scene::create();
	return scene;
}

edge::Scene* SceneCreator::createDemoScene()
{
	Scene* scene = Scene::create();

	scene->addComponent(DemoComponent::create(scene));

	return scene;
}
