/********************************************
名称:
说明:
1.
********************************************/

#ifndef __SCENE_H_H__
#define __SCENE_H_H__

#include "GameObject.h"

NS_EDGE_BEGIN

class EDGE_DLL Scene final : public GameObject
{
public:
	static Scene* create();
	static Scene* create(const std::string& sceneFilename);
	~Scene();

private:
	Scene();
	bool initWithFile(const std::string& sceneFilename);
};

NS_EDGE_END

#endif // __SCENE_H_H__