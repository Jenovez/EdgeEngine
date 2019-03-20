/********************************************
名称:
说明:
1.
********************************************/

#ifndef __XAUDIO2_FACTORY_H_H__
#define __XAUDIO2_FACTORY_H_H__

#include <audio/IAudioFactory.h>

NS_EDGE_BEGIN

class EDGE_DLL XAudio2Factory final : public IAudioFactory
{
public:
	XAudio2Factory();
	~XAudio2Factory();

	IAudioCircumstance* createAudioCircumstance();
	IAudioDecoder* createAudioDecoder();
	IAudio* createAudio(IAudioCircumstance* circumstance);
};

NS_EDGE_END

#endif // __XAUDIO2_FACTORY_H_H__