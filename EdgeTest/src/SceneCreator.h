/********************************************
名称:
说明:
1.
********************************************/

#ifndef __SCENE_CREATOR_H_H__
#define __SCENE_CREATOR_H_H__

#include <edge.h>

class SceneCreator
{
public:
	static edge::Scene* createLogoScene();
	static edge::Scene* createGameRunScene();
	static edge::Scene* createFinishScene();
	static edge::Scene* createDemoScene();
};

#endif // __SCENE_CREATOR_H_H__