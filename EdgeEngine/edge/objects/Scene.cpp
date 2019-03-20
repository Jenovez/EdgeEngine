// cpp文件

#include "Scene.h"

#include <rapidjson/include/document.h>
#include <edge.h>

USING_NS_EDGE;

Scene* Scene::create()
{
	auto ret = new Scene();
	ret->autorelease();
	return ret;
}

Scene* Scene::create(const std::string& sceneFilename)
{
	auto ret = new Scene();
	if (ret->initWithFile(sceneFilename))
	{
		ret->autorelease();
	}
	else
	{
		delete ret;
		ret = NULL;
	}
	return ret;
}

Scene::Scene()
{}

bool Scene::initWithFile(const std::string& sceneFilename)
{
	//std::string sceneStr = FileUtils::readStringFromFile(sceneFilename);
	//rapidjson::Document doc;
	//doc.Parse<0>(sceneStr.c_str());
	//if (doc.GetParseError() != rapidjson::ParseErrorCode::kParseErrorNone)
	//{
	//	return false;
	//}

	//auto logoObj = GameObject::create();
	//addGameObject(logoObj);
	//logoObj->addComponent(SpriteComponent::create(doc["obj"].GetString()));
	//logoObj->setTransformComponent(TransformComponent::create());
	//logoObj->getTransformComponent()->Position.setValue(400, 300);

	return true;
}

Scene::~Scene()
{}