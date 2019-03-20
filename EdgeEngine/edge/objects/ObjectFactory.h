/********************************************
名称:
说明:
1.
********************************************/

#ifndef __OBJECT_FACTORY_H_H__
#define __OBJECT_FACTORY_H_H__

#include "GameObject.h"

NS_EDGE_BEGIN

class EDGE_DLL ObjectFactory
{
public:
	static GameObject* createSpriteObject();
	static GameObject* createSpriteObject(const std::string& filename);
	static GameObject* createSpriteObject(int cacheTag, const Data& data);

	static GameObject* createAudioObject();
	static GameObject* createAudioObject(const std::string& filename);
};

NS_EDGE_END

#endif // __OBJECT_FACTORY_H_H__