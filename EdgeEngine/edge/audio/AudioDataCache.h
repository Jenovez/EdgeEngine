/********************************************
名称:
说明:
1.
********************************************/

#ifndef __AUDIO_DATA_CACHE_H_H__
#define __AUDIO_DATA_CACHE_H_H__

#include "AudioCommon.h"

NS_EDGE_BEGIN

class EDGE_DLL AudioDataCache final
{
public:
	AudioDataCache();
	~AudioDataCache();

	void insertAudioData(const std::string& tagName, AudioData* data);
	void insertAudioData(int tag, AudioData* data);

	void removeAudioData(const std::string& tagName);
	void removeAudioData(int tag);

	AudioData* getAudioData(const std::string& tagName) const;
	AudioData* getAudioData(int tag) const;

	void clear();

private:
	std::map<std::string, AudioData*> _strCacheList;
	std::map<int, AudioData*> _tagCacheList;
};

NS_EDGE_END

#endif // __AUDIO_DATA_CACHE_H_H__