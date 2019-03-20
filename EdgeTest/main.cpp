// cpp文件
#include "edge.h"
#pragma comment(lib, "EdgeEngine")

#include "src/SceneCreator.h"

USING_NS_EDGE;

int EdgeMain()
{
	Director::getInstance()->runScene(SceneCreator::createLogoScene());
	//Director::getInstance()->runScene(SceneCreator::createDemoScene());
	//Director::getInstance()->runScene(SceneCreator::createGameRunScene());

	return 0;
}

int main(int argc, char** argv)
{
	Application app;
	return app.run(EdgeMain);
}