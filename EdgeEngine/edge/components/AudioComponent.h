/********************************************
名称:
说明:
1.
********************************************/

#ifndef __AUDIO_COMPONENT_H_H__
#define __AUDIO_COMPONENT_H_H__

#include "Component.h"

NS_EDGE_BEGIN

class EDGE_DLL AudioComponent : public Component
{
public:
	static AudioComponent* create();
	static AudioComponent* create(const std::string& filename);

	virtual ~AudioComponent();
	
	bool setAudioData(const std::string& filename);

	void setOnStartPlayEnable(bool b);
	bool isOnStartPlayEnable() const;

	IAudio* getAudio() const;

public:
	virtual void onEnter();
	virtual void onExit();
	virtual void onStart();

	virtual void onFastUpdate(double dt);
	virtual void onUpdate(double dt);
	virtual void onLateUpdate(double dt);
	virtual void onRender(double dt);

protected:
	AudioComponent();
	bool init();

private:
	IAudio* _audio;

	bool m_bOnStartPlayEnable;
};

NS_EDGE_END

#endif // __AUDIO_COMPONENT_H_H__