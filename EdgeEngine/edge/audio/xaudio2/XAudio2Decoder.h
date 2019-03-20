/********************************************
名称:
说明:
1.
********************************************/

#ifndef __XAUDIO2_DECODER_H_H__
#define __XAUDIO2_DECODER_H_H__

#include <audio/IAudioDecoder.h>

NS_EDGE_BEGIN

class EDGE_DLL XAudio2Decoder final : public IAudioDecoder
{
public:
	AudioData* getMp3DataFromFile(const std::string& filename);
	AudioData* getOggDataFromFile(const std::string& filename);
	AudioData* getWavDataFromFile(const std::string& filename);
};

NS_EDGE_END

#endif // __XAUDIO2_DECODER_H_H__