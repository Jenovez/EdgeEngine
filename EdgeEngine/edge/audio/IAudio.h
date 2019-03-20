/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_AUDIO_H_H__
#define __I_AUDIO_H_H__

#include "AudioCommon.h"

NS_EDGE_BEGIN

class IAudio;

class EDGE_DLL IAudioListener
{
public:
	virtual void audioPlay(IAudio* audio) = 0;
	virtual void audioStop(IAudio* audio) = 0;
	virtual void audioPause(IAudio* audio) = 0;
	virtual void audioPlaying(IAudio* audio) = 0;
};

class EDGE_DLL IAudio
{
public:
	virtual ~IAudio() {}

	/**
	* 绑定音频数据
	*/
	virtual void bindAudioData(AudioData* data) = 0;

	/**
	* 获得绑定的音频数据
	*/
	virtual AudioData* getAudioData() const = 0;

	/**
	* 播放
	*/
	virtual bool play() = 0;
	/**
	* 停止
	*/
	virtual void stop() = 0;
	/**
	* 暂停
	*/
	virtual void pause() = 0;
	/**
	* 继续
	* 在暂停之后
	*/
	virtual void resume() = 0;
	/**
	* 重置
	* 会停止播放
	*/
	virtual void reset() = 0;
	/**
	* 更新
	*/
	virtual void update() = 0;
	/**
	* 跳转
	* 参数:跳转到指定秒数的位置
	*/
	virtual void jump(UInt second) = 0;
	/**
	* 前进
	* 参数1:前进秒数
	*/
	virtual void next(UInt stepSec) = 0;
	/**
	* 后退
	* 参数1:后退秒数
	*/
	virtual void back(UInt stepSec) = 0;
	/**
	* 获得当前播放的位置
	*/
	virtual UInt getCurrentTime() const = 0;

	/**
	* 添加音频监听器
	*/
	virtual void addListener(IAudioListener* listener) = 0;
	virtual void removeListener(IAudioListener* listener) = 0;

	/**
	* 设置播放起始位置
	* 参数:秒,默认值(0)
	*/
	virtual void setPlayBeginTime(UInt second) = 0;
	virtual UInt getPlayBeginTime() const = 0;

	/**
	* 设置播放长度
	* 参数:秒,默认值(0)表示播放到结尾
	*/
	virtual void setPlayTimeLength(UInt second) = 0;
	virtual UInt getPlayTimeLength() const = 0;

	/**
	* 设置循环播放的起始位置
	* 参数:秒,默认值(0)
	*/
	virtual void setLoopBeginTime(UInt second) = 0;
	virtual UInt getLoopBeginTime() const = 0;

	/**
	* 设置循环播放的长度
	* 参数:秒, 默认值(0)表示播放到结尾
	*/
	virtual void setLoopTimeLength(UInt second) = 0;
	virtual UInt getLoopTimeLength() const = 0;

	/**
	* 设置循环次数
	* 参数:循环次数,默认(0)表示只播放一次,不循环
	* 设置为-1表示无限循环
	*/
	virtual void setLoopCounts(UInt counts) = 0;
	virtual UInt getLoopCounts() const = 0;

	/**
	* 设置音量
	* 参数:范围(0 - 1),默认:(1)
	*/
	virtual void setVolume(float volume) = 0;
	virtual float getVolume() const = 0;

	virtual bool isPlaying() = 0;
};

NS_EDGE_END

#endif // __I_AUDIO_H_H__