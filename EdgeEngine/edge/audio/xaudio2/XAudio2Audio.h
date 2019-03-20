/********************************************
名称:
说明:
1.
********************************************/

#ifndef __XAUDIO2_AUDIO_H_H__
#define __XAUDIO2_AUDIO_H_H__

#include <audio/IAudio.h>
#include "lib-xaudio2.h"

NS_EDGE_BEGIN

class XAudio2Circumstance;

class EDGE_DLL XAudio2Audio final : public IAudio
{
public:
	XAudio2Audio(IXAudio2* xaudio2);
	~XAudio2Audio();

	/**
	* 绑定音频数据
	*/
	void bindAudioData(AudioData* data);

	/**
	* 获得绑定的音频数据
	*/
	AudioData* getAudioData() const;

	/**
	* 播放
	*/
	bool play();
	/**
	* 停止
	*/
	void stop();
	/**
	* 暂停
	*/
	void pause();
	/**
	* 继续
	* 在暂停之后
	*/
	void resume();
	/**
	* 重置
	* 会停止播放
	*/
	void reset();
	/**
	* 更新
	*/
	void update();
	/**
	* 跳转
	* 参数:跳转到指定秒数的位置
	*/
	void jump(UInt second);
	/**
	* 前进
	* 参数1:前进秒数
	*/
	void next(UInt stepSec);
	/**
	* 后退
	* 参数1:后退秒数
	*/
	void back(UInt stepSec);
	/**
	* 获得当前播放的位置
	*/
	UInt getCurrentTime() const;

	/**
	* 添加音频监听器
	*/
	void addListener(IAudioListener* listener);
	void removeListener(IAudioListener* listener);

	/**
	* 设置播放起始位置
	* 参数:秒,默认值(0)
	*/
	void setPlayBeginTime(UInt second);
	UInt getPlayBeginTime() const;

	/**
	* 设置播放长度
	* 参数:秒,默认值(0)表示播放到结尾
	*/
	void setPlayTimeLength(UInt second);
	UInt getPlayTimeLength() const;

	/**
	* 设置循环播放的起始位置
	* 参数:秒,默认值(0)
	*/
	void setLoopBeginTime(UInt second);
	UInt getLoopBeginTime() const;

	/**
	* 设置循环播放的长度
	* 参数:秒, 默认值(0)表示播放到结尾
	*/
	void setLoopTimeLength(UInt second);
	UInt getLoopTimeLength() const;

	/**
	* 设置循环次数
	* 参数:循环次数,默认(0)表示只播放一次,不循环
	* 设置为-1表示无限循环
	*/
	void setLoopCounts(UInt counts);
	UInt getLoopCounts() const;

	/**
	* 设置音量
	* 参数:范围(0 - 1),默认:(1)
	*/
	void setVolume(float volume);
	float getVolume() const;

	bool isPlaying();

private:
	AudioData* _data; // data chunk
	XAUDIO2_BUFFER _buffer; // xaudio buffer
	IXAudio2* _xaudio2; // xaudio2 reference
	IXAudio2SourceVoice* _lpSourceVoice; // audio source

private:
	std::vector<IAudioListener*> _audioListenerList;
	float m_fVolume;
	UInt m_iCurrentTime; // 当前时间
	UInt m_iPlayBeginTime;
	UInt m_iPlayTimeLength;
	UInt m_iLoopBeginTime;
	UInt m_iLoopTimeLength;
};

NS_EDGE_END

#endif // __XAUDIO2_AUDIO_H_H__