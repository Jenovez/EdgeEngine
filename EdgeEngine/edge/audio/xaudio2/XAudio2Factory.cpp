// cpp文件

#include "XAudio2Factory.h"

#include "XAudio2Audio.h"
#include "XAudio2Circumstance.h"
#include "XAudio2Decoder.h"

USING_NS_EDGE;

XAudio2Factory::XAudio2Factory()
{}

XAudio2Factory::~XAudio2Factory()
{}

IAudioCircumstance* XAudio2Factory::createAudioCircumstance()
{
	return new XAudio2Circumstance();
}

IAudioDecoder* XAudio2Factory::createAudioDecoder()
{
	return new XAudio2Decoder();
}

IAudio* XAudio2Factory::createAudio(IAudioCircumstance* circumstance)
{
	return new XAudio2Audio(((XAudio2Circumstance*)circumstance)->getXAudio2());
}