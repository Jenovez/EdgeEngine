// cpp文件

#include "XAudio2Audio.h"
#include "XAudio2Circumstance.h"

USING_NS_EDGE;

XAudio2Audio::XAudio2Audio(IXAudio2* xaudio2)
	: _data(NULL)
	, _buffer()
	, _xaudio2(xaudio2)
	, _lpSourceVoice(NULL)
	, _audioListenerList()
	, m_fVolume(1)
	, m_iCurrentTime(0)
	, m_iPlayBeginTime(0)
	, m_iPlayTimeLength(0)
	, m_iLoopBeginTime(0)
	, m_iLoopTimeLength(0)
{
	assert(_xaudio2);
	ZeroMemory(&_buffer, sizeof(XAUDIO2_BUFFER));
}

XAudio2Audio::~XAudio2Audio()
{
	XAudio2::SafeVoiceDestroy(&_lpSourceVoice);
}

void XAudio2Audio::bindAudioData(AudioData* data)
{
	_data = data;
	XAudio2::SafeVoiceDestroy(&_lpSourceVoice);
	if (_data)
	{
		if (!_data->data.bin || !_data->data.size) { return; }
		// 辅缓冲区格式类型
		WAVEFORMATEX wfx;
		ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
		wfx.wFormatTag = WAVE_FORMAT_PCM;
		// 双通道
		wfx.nChannels = _data->NumberOfChannels;
		// 平均采样频率
		wfx.nSamplesPerSec = _data->SampleRate;
		// 每个采样点占16位
		wfx.wBitsPerSample = _data->BitsPerSample;
		wfx.nBlockAlign = _data->BlockAlign;
		wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
		HRESULT hr = _xaudio2->CreateSourceVoice(&_lpSourceVoice, &wfx, 0, XAUDIO2_DEFAULT_FREQ_RATIO);
		assert(_lpSourceVoice);
	}
	reset();
}

AudioData* XAudio2Audio::getAudioData() const { return _data; }
bool XAudio2Audio::play()
{
	if (!_lpSourceVoice) { return false; }
	HRESULT hr = NULL;
	_lpSourceVoice->FlushSourceBuffers();
	hr = _lpSourceVoice->SubmitSourceBuffer(&_buffer);
	if (SUCCEEDED(hr))
	{
		setVolume(getVolume());
		hr = _lpSourceVoice->Start();
		for (auto lis : _audioListenerList)
		{
			lis->audioPlay(this);
		}
	}
	return SUCCEEDED(hr);
}

void XAudio2Audio::stop()
{
	if (!_lpSourceVoice) { return; }
	_lpSourceVoice->FlushSourceBuffers();
	_lpSourceVoice->Stop();
	for (auto lis : _audioListenerList)
	{
		lis->audioStop(this);
	}
}

void XAudio2Audio::pause()
{
	if (isPlaying())
	{
		stop();
		m_iCurrentTime = 0;
		for (auto lis : _audioListenerList)
		{
			lis->audioPause(this);
		}
	}
}

void XAudio2Audio::resume()
{
	if (!_data) { return; }
	UInt tempBegin = _buffer.PlayBegin;
	_buffer.PlayBegin = (UInt)((double)m_iCurrentTime / (double)_data->TotalTime * (double)_data->SoundLength);
	play();
	_buffer.PlayBegin = tempBegin;
}

void XAudio2Audio::reset()
{
	ZeroMemory(&_buffer, sizeof(XAUDIO2_BUFFER));
	if (_data)
	{
		_buffer.AudioBytes = _data->data.size;
		_buffer.pAudioData = _data->data.bin;
	}
	else
	{
		_buffer.AudioBytes = 0;
		_buffer.pAudioData = NULL;;
	}
	m_iCurrentTime = 0;
	m_fVolume = 1;
	m_iPlayBeginTime = 0;
	m_iPlayTimeLength = 0;
	m_iLoopBeginTime = 0;
	m_iLoopTimeLength = 0;
	stop();
}

void XAudio2Audio::update()
{
	if (_data)
	{
		XAUDIO2_VOICE_STATE state;
		_lpSourceVoice->GetState(&state);
		auto currentPos = (UInt)(_buffer.PlayBegin + state.SamplesPlayed);
		m_iCurrentTime = (UInt)((double)currentPos / (double)_data->SoundLength * (double)_data->TotalTime);
		if (state.SamplesPlayed != 0)
		{
			for (auto lis : _audioListenerList)
			{
				lis->audioPlaying(this);
			}
		}
	}
}

void XAudio2Audio::jump(UInt second)
{
	if (!_data) { return; }
	m_iCurrentTime = second;
	if (m_iCurrentTime > _data->TotalTime)
	{
		m_iCurrentTime = _data->TotalTime;
	}
	resume();
}

void XAudio2Audio::next(UInt stepSec)
{
	if (!_data) { return; }
	m_iCurrentTime += stepSec;
	if (m_iCurrentTime > _data->TotalTime)
	{
		m_iCurrentTime = _data->TotalTime;
	}
	resume();
}

void XAudio2Audio::back(UInt stepSec)
{
	if (m_iCurrentTime < stepSec)
	{
		m_iCurrentTime = 0;
	}
	else
	{
		m_iCurrentTime -= stepSec;
	}
	resume();
}

UInt XAudio2Audio::getCurrentTime() const { return m_iCurrentTime; }
void XAudio2Audio::addListener(IAudioListener* listener)
{
	assert(listener);
	if (!listener) { return; }
	_audioListenerList.push_back(listener);
}
void XAudio2Audio::removeListener(IAudioListener* listener)
{
	auto ite = std::find(_audioListenerList.begin(), _audioListenerList.end(), listener);
	if (ite != _audioListenerList.end())
	{
		_audioListenerList.erase(ite);
	}
}
void XAudio2Audio::setPlayBeginTime(UInt second)
{
	if (!_data) { return; }
	m_iPlayBeginTime = second;
	_buffer.PlayBegin = (UInt)((double)m_iPlayBeginTime / (double)_data->TotalTime * (double)_data->SoundLength);
}
UInt XAudio2Audio::getPlayBeginTime() const { return m_iPlayBeginTime; }
void XAudio2Audio::setPlayTimeLength(UInt second)
{
	if (!_data) { return; }
	m_iPlayTimeLength = second;
	_buffer.PlayLength = (UInt)((double)m_iPlayTimeLength / (double)_data->TotalTime * (double)_data->SoundLength);
}
UInt XAudio2Audio::getPlayTimeLength() const { return m_iPlayTimeLength; }
void XAudio2Audio::setLoopBeginTime(UInt second)
{
	if (!_data) { return; }
	m_iLoopBeginTime = second;
	_buffer.LoopBegin = (UInt)((double)m_iLoopBeginTime / (double)_data->TotalTime * (double)_data->SoundLength);
}
UInt XAudio2Audio::getLoopBeginTime() const { return m_iLoopBeginTime; }
void XAudio2Audio::setLoopTimeLength(UInt second)
{
	if (!_data) { return; }
	m_iLoopTimeLength = second;
	_buffer.LoopLength = (UInt)((double)m_iLoopTimeLength / (double)_data->TotalTime * (double)_data->SoundLength);
}
UInt XAudio2Audio::getLoopTimeLength() const { return m_iLoopTimeLength; }
void XAudio2Audio::setLoopCounts(UInt counts) { _buffer.LoopCount = counts; }
UInt XAudio2Audio::getLoopCounts() const { return _buffer.LoopCount; }
void XAudio2Audio::setVolume(float volume) { m_fVolume = volume; }
float XAudio2Audio::getVolume() const { return m_fVolume; }
bool XAudio2Audio::isPlaying()
{
	if (!_lpSourceVoice) { return false; }
	XAUDIO2_VOICE_STATE state;
	_lpSourceVoice->GetState(&state);
	return (state.SamplesPlayed != 0);
}
