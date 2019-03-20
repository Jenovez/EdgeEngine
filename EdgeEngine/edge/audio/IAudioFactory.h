/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_AUDIO_FACTORY_H_H__
#define __I_AUDIO_FACTORY_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>

NS_EDGE_BEGIN

class IAudio;
class IAudioCircumstance;
class IAudioDecoder;

class EDGE_DLL IAudioFactory
{
public:
	virtual ~IAudioFactory() {}

	virtual IAudioCircumstance* createAudioCircumstance() = 0;
	virtual IAudioDecoder* createAudioDecoder() = 0;
	virtual IAudio* createAudio(IAudioCircumstance* circumstance) = 0;
};

NS_EDGE_END

#endif // __I_AUDIO_FACTORY_H_H__