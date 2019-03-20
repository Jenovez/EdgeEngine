/********************************************
名称:
说明:
1.
********************************************/

#ifndef __COMPONENT_H_H__
#define __COMPONENT_H_H__

#include <base/Object.h>

#include <base/Director.h>
#include <platform/PlatformManager.h>
#include <audio/AudioManager.h>
#include <renderer/RendererManager.h>

NS_EDGE_BEGIN

class GameObject;

class EDGE_DLL Component : public Object
{
protected:
	Component();

public:
	virtual ~Component();

	virtual void setZOrder(int order) final;
	virtual int getZOrder() const final;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

public:
	virtual void onStart() = 0;
	virtual void onFastUpdate(double dt) = 0;
	virtual void onUpdate(double dt) = 0;
	virtual void onLateUpdate(double dt) = 0;
	virtual void onRender(double dt) = 0;

public:
	Director* getDirector() const;
	AudioManager* getAudioManager() const;
	RendererManager* getRendererManager() const;
	PlatformManager* getPlatformManager() const;
	
private:
	int m_iZOrder;

protected:
	friend class GameObject;
	GameObject* _gameObject;

	Director* _refDirector;
	AudioManager* _refAudioManager;
	RendererManager* _refRenderermanager;
	PlatformManager* _refPlatformManager;

	bool m_bStart;
};

NS_EDGE_END

#endif // __COMPONENT_H_H__