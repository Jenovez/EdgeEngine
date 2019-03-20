/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECTOR_H_H__
#define __DIRECTOR_H_H__

#include "CommonConfig.h"
#include "EdgeTypes.h"
#include <objects/Scene.h>

NS_EDGE_BEGIN

class Application;
class AudioManager;
class RendererManager;
class PlatformManager;

class EDGE_DLL Director final
{
public:
	static Director* getInstance();

	void onFastUpdate(double dt);
	void onUpdate(double dt);
	void onLateUpdate(double dt);
	void onRender(double dt);

	void runScene(Scene* scene);
	Scene* getScene() const;

	void shutDown();

public:
	void locatorApplication(Application* application);
	Application* getApplication() const;

	void locatorAudioManager(AudioManager* mgr);
	AudioManager* getAudioManager() const;

	void locatorRendererManager(RendererManager* mgr);
	RendererManager* getRendererManager() const;

	void locatorPlatformManager(PlatformManager* mgr);
	PlatformManager* getPlatformManager() const;


private:
	Director();
	~Director();
	Director(const Director&);
	Director& operator=(const Director&);

private:
	Application* _application;
	AudioManager* _audioManager;
	RendererManager* _rendererManager;
	PlatformManager* _platformManager;

private:
	Scene* _runningScene;
};

NS_EDGE_END

#endif // __DIRECTOR_H_H__