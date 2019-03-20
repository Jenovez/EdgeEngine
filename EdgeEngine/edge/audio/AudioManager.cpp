// cpp文件

#include "AudioManager.h"

#include <rapidjson/include/document.h>
#include <rapidjson/include/writer.h>
#include <utils/FileUtils.h>
#include <platform/PlatformManager.h>

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "xaudio2/XAudio2Factory.h"
#endif

#define AudioConfigPath "engine/audio.config"

USING_NS_EDGE;

AudioManager* AudioManager::getInstance()
{
	static AudioManager _ins;
	return &_ins;
}

AudioManager::AudioManager()
	: _factory(NULL)
	, _audioCircumstance(NULL)
	, _audioDecoder(NULL)
	, _audioCache(NULL)
	, _audioType(AUDIO_TYPE::NONE)
{}

AudioManager::~AudioManager()
{
}

bool AudioManager::loadConfig()
{
	if (!FileUtils::isFileExist(AudioConfigPath)) { return false; }
	rapidjson::Document doc;
	std::string jsonStr = FileUtils::readStringFromFile(AudioConfigPath);
	doc.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());
	rapidjson::ParseErrorCode err = doc.GetParseError();
	if (doc.GetParseError() != rapidjson::ParseErrorCode::kParseErrorNone) { return false; }
	_audioType = (AUDIO_TYPE)doc["AudioType"].GetInt();

	return true;
}

void AudioManager::saveConfig()
{
	rapidjson::Document doc;
	doc.SetObject();
	doc.AddMember("AudioType", (int)_audioType, doc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	std::string jsonStr = buffer.GetString();
	jsonStr.append("\n");
	bool ret = FileUtils::writeStringToFile(AudioConfigPath, jsonStr);
	assert(ret);
}

void AudioManager::resetConfig()
{
#if TARGET_PLATFORM == PLATFORM_WIN32
	_audioType = AUDIO_TYPE::XAUDIO2;
#else
	_audioType = AUDIO_TYPE::OPENAL;
#endif
}

bool AudioManager::startUp()
{
	clearAudio();
	SAFE_DELETE(_factory);
	SAFE_DELETE(_audioCache);
	SAFE_DELETE(_audioDecoder);
	SAFE_DELETE(_audioCircumstance);

	switch (_audioType)
	{
	case edge::AUDIO_TYPE::OPENAL:
		break;
#if TARGET_PLATFORM == PLATFORM_WIN32
	case edge::AUDIO_TYPE::XAUDIO2:
		_factory = new XAudio2Factory();
		break;
#endif
	default: return false;
	}

	_audioCircumstance = _factory->createAudioCircumstance();
	_audioDecoder = _factory->createAudioDecoder();
	_audioCache = new AudioDataCache();

	if (!_audioCircumstance->initAudio(
		PlatformManager::getInstance()->getWindow()))
	{
		return false;
	}

	return true;
}

bool AudioManager::shutDown()
{
	clearAudio();
	SAFE_DELETE(_factory);
	SAFE_DELETE(_audioCache);
	SAFE_DELETE(_audioDecoder);
	SAFE_DELETE(_audioCircumstance);
	return true;
}

void AudioManager::beginUpdate()
{}

void AudioManager::update()
{
	for (auto audio : _audioList)
	{
		audio->update();
	}
}

void AudioManager::endUpdate()
{}

bool AudioManager::isStop()
{
	return false;
}

IAudio* AudioManager::createAudio()
{
	return _factory->createAudio(_audioCircumstance);
}

void AudioManager::pushAudio(IAudio* audio)
{
	assert(audio);
	_audioList.push_back(audio);
}

void AudioManager::removeAudio(IAudio* audio)
{
	auto ite = std::find(_audioList.begin(), _audioList.end(), audio);
	if (ite != _audioList.end())
	{
		delete *ite;
		_audioList.erase(ite);
	}
}

void AudioManager::clearAudio()
{
	for (auto audio : _audioList)
	{
		delete audio;
	}
	_audioList.clear();
}

IAudioCircumstance* AudioManager::getAudioCircumstance() const { return _audioCircumstance; }
IAudioDecoder* AudioManager::getAudioDecoder() const { return _audioDecoder; }
AudioDataCache* AudioManager::getAudioDataCache() const { return _audioCache; }
