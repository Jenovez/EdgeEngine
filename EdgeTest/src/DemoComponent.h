/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DEMO_COMPONENT_H_H__
#define __DEMO_COMPONENT_H_H__

#include <edge.h>

NS_EDGE_BEGIN

class DemoComponent final : public Component
{
public:
	static DemoComponent* create(Scene* runScene);

public:
	void onEnter();
	void onExit();
	void onStart();
	void onFastUpdate(double dt);
	void onUpdate(double dt);
	void onLateUpdate(double dt);
	void onRender(double dt);

private:
	DemoComponent();
	~DemoComponent();

private:
	Scene* _currentScene;

	std::vector<GameObject*> _effList;
};

NS_EDGE_END

#endif // __DEMO_COMPONENT_H_H__