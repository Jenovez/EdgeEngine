// cpp文件

#include "XAudio2Circumstance.h"

USING_NS_EDGE;

XAudio2Circumstance::XAudio2Circumstance()
	: _lpXAudio2(NULL)
	, _lpMasteringVoice(NULL)
{
}

XAudio2Circumstance::~XAudio2Circumstance()
{
	XAudio2::SafeVoiceDestroy(&_lpMasteringVoice);
	XAudio2::SafeRelease(&_lpXAudio2);
}

bool XAudio2Circumstance::initAudio(IWindow* window)
{
	HRESULT hr = NULL;
	hr = XAudio2Create(&_lpXAudio2);
	if (SUCCEEDED(hr))
	{
		hr = _lpXAudio2->CreateMasteringVoice(&_lpMasteringVoice);
	}

	return SUCCEEDED(hr);
}

IXAudio2* XAudio2Circumstance::getXAudio2() const { return _lpXAudio2; }
IXAudio2MasteringVoice* XAudio2Circumstance::getXAudio2MasteringVoice() const { return _lpMasteringVoice; }