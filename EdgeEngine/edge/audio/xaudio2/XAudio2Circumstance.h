/********************************************
名称:
说明:
1.
********************************************/

#ifndef __XAUDIO2_CIRCUMSTANCE_H_H__
#define __XAUDIO2_CIRCUMSTANCE_H_H__

#include <audio/IAudioCircumstance.h>
#include "lib-xaudio2.h"

NS_EDGE_BEGIN

class EDGE_DLL XAudio2Circumstance final : public IAudioCircumstance
{
public:
	XAudio2Circumstance();
	~XAudio2Circumstance();

	bool initAudio(IWindow* window);

public:
	IXAudio2* getXAudio2() const;
	IXAudio2MasteringVoice* getXAudio2MasteringVoice() const;

private:
	IXAudio2* _lpXAudio2;
	IXAudio2MasteringVoice* _lpMasteringVoice;
};

NS_EDGE_END

#endif // __XAUDIO2_CIRCUMSTANCE_H_H__