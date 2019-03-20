// cpp文件

#include "AudioComponent.h"

USING_NS_EDGE;

AudioComponent* AudioComponent::create()
{
	AudioComponent* ret = new AudioComponent();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		SAFE_DELETE(ret);
	}
	return ret;
}

AudioComponent* AudioComponent::create(const std::string& filename)
{
	AudioComponent* ret = new AudioComponent();
	if (ret && ret->init() && ret->setAudioData(filename))
	{
		ret->autorelease();
	}
	else
	{
		SAFE_DELETE(ret);
	}
	return ret;
}

AudioComponent::~AudioComponent()
{
	auto lastData = _audio->getAudioData();
	SAFE_DELETE(lastData);
	_refAudioManager->removeAudio(_audio);
}

bool AudioComponent::setAudioData(const std::string& filename)
{
	std::string exName = filename.substr(filename.find_last_of('.', filename.length()), 4);
	auto audioDecoder = _refAudioManager->getAudioDecoder();
	AudioData* audioData = NULL;
	if (exName == ".mp3")
	{
		audioData = audioDecoder->getMp3DataFromFile(filename);
	}
	else if (exName == ".ogg")
	{
		audioData = audioDecoder->getOggDataFromFile(filename);
	}
	else if (exName == ".wav")
	{
		audioData = audioDecoder->getWavDataFromFile(filename);
	}
	auto lastData = _audio->getAudioData();
	SAFE_DELETE(lastData);
	_audio->bindAudioData(audioData);

	return (audioData != NULL);
}

void AudioComponent::setOnStartPlayEnable(bool b) { m_bOnStartPlayEnable = b; }
bool AudioComponent::isOnStartPlayEnable() const { return m_bOnStartPlayEnable; }

IAudio* AudioComponent::getAudio() const { return _audio; }

void AudioComponent::onEnter()
{}

void AudioComponent::onExit()
{}

void AudioComponent::onStart()
{
	if (m_bOnStartPlayEnable)
	{
		_audio->play();
	}
}

void AudioComponent::onFastUpdate(double dt)
{}

void AudioComponent::onUpdate(double dt)
{}

void AudioComponent::onLateUpdate(double dt)
{}

void AudioComponent::onRender(double dt)
{}

AudioComponent::AudioComponent()
	: _audio(NULL)
	, m_bOnStartPlayEnable(true)
{
}

bool AudioComponent::init()
{
	if (!_audio)
	{
		_audio = _refAudioManager->createAudio();
		if (_audio)
		{
			_refAudioManager->pushAudio(_audio);
		}
	}
	return (_audio != NULL);
}
