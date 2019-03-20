/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_AUDIO_DECODER_H_H__
#define __I_AUDIO_DECODER_H_H__

#include "AudioCommon.h"

NS_EDGE_BEGIN

class EDGE_DLL IAudioDecoder
{
public:
	virtual ~IAudioDecoder() {}

	virtual AudioData* getMp3DataFromFile(const std::string& filename) = 0;
	virtual AudioData* getOggDataFromFile(const std::string& filename) = 0;
	virtual AudioData* getWavDataFromFile(const std::string& filename) = 0;
};

NS_EDGE_END

#endif // __I_AUDIO_DECODER_H_H__