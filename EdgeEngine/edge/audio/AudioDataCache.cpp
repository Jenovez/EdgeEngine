// cpp文件

#include "AudioDataCache.h"

USING_NS_EDGE;

AudioDataCache::AudioDataCache()
	: _strCacheList()
	, _tagCacheList()
{
}

AudioDataCache::~AudioDataCache()
{
	clear();
}

void AudioDataCache::insertAudioData(const std::string& tagName, AudioData* data)
{
	assert(data);
	assert(!getAudioData(tagName));
	_strCacheList[tagName] = data;
}

void AudioDataCache::insertAudioData(int tag, AudioData* data)
{
	assert(data);
	assert(!getAudioData(tag));
	_tagCacheList[tag] = data;
}

void AudioDataCache::removeAudioData(const std::string& tagName)
{
	auto ite = _strCacheList.find(tagName);
	if (ite != _strCacheList.end())
	{
		delete ite->second;
		_strCacheList.erase(ite);
	}
}

void AudioDataCache::removeAudioData(int tag)
{
	auto ite = _tagCacheList.find(tag);
	if (ite != _tagCacheList.end())
	{
		delete ite->second;
		_tagCacheList.erase(ite);
	}
}

AudioData* AudioDataCache::getAudioData(const std::string& tagName) const
{
	auto ite = _strCacheList.find(tagName);
	if (ite != _strCacheList.end())
	{
		return ite->second;
	}
	return NULL;
}

AudioData* AudioDataCache::getAudioData(int tag) const
{
	auto ite = _tagCacheList.find(tag);
	if (ite != _tagCacheList.end())
	{
		return ite->second;
	}
	return NULL;
}

void AudioDataCache::clear()
{
	for (auto& pair : _strCacheList)
	{
		delete pair.second;
	}
	_strCacheList.clear();
	for (auto& pair : _tagCacheList)
	{
		delete pair.second;
	}
	_tagCacheList.clear();
}