/********************************************
名称:
说明:
1.
********************************************/

#ifndef __AUDIO_MANAGER_H_H__
#define __AUDIO_MANAGER_H_H__

#include <base/IManagerProtocol.h>
#include "AudioCommon.h"
#include "AudioConfig.h"

#include "IAudio.h"
#include "IAudioCircumstance.h"
#include "IAudioDecoder.h"
#include "IAudioFactory.h"
#include "AudioDataCache.h"

NS_EDGE_BEGIN

class EDGE_DLL AudioManager final : public IManagerProtocol
{
public:
	static AudioManager* getInstance();

	bool loadConfig();
	void saveConfig();
	void resetConfig();

	bool startUp();
	bool shutDown();

	void beginUpdate();
	void update();
	void endUpdate();

	bool isStop();

public:
	IAudio* createAudio();

	void pushAudio(IAudio* audio);
	void removeAudio(IAudio* audio);
	void clearAudio();

public:
	IAudioCircumstance* getAudioCircumstance() const;
	IAudioDecoder* getAudioDecoder() const;

	AudioDataCache* getAudioDataCache() const;

private:
	AudioManager();
	~AudioManager();
	AudioManager(const AudioManager&);
	AudioManager& operator=(const AudioManager&);

private:
	IAudioFactory* _factory;
	IAudioCircumstance* _audioCircumstance;
	IAudioDecoder* _audioDecoder;
	AudioDataCache* _audioCache;
	AUDIO_TYPE _audioType;

	std::vector<IAudio*> _audioList;
};

NS_EDGE_END

#endif // __AUDIO_MANAGER_H_H__