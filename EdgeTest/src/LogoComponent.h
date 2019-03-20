/********************************************
名称:
说明:
1.
********************************************/

#ifndef __LOGO_COMPONENT_H_H__
#define __LOGO_COMPONENT_H_H__

#include <edge.h>

NS_EDGE_BEGIN

class LogoComponent final : public Component
{
public:
	static LogoComponent* create(Scene* runScene);

public:
	void onEnter();
	void onExit();
	void onStart();
	void onFastUpdate(double dt);
	void onUpdate(double dt);
	void onLateUpdate(double dt);
	void onRender(double dt);

private:
	LogoComponent();
	~LogoComponent();

private:
	Scene* _currentScene;

	ImageComponent* _logo;

	int state;
};

NS_EDGE_END

#endif // __LOGO_COMPONENT_H_H__