/********************************************
名称:
说明:
1.
********************************************/

#ifndef __AUDIO_COMMON_H_H__
#define __AUDIO_COMMON_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>

NS_EDGE_BEGIN

struct EDGE_DLL AudioData
{
	std::string Filename;
	Data data; // 数据块
	int AudioFormat; // 音频格式: WAVE_FORMAT_PCM
	int NumberOfChannels; // 通道数
	int SampleRate; // 采样率
	int ByteRate; // 样本字节: SampleRate * NumberOfChannels * (BitsPerSample / 8)
	int BlockAlign; // 对齐的(平均)块数据大小: SampleRate * (BitsPerSample / 8)
	int BitsPerSample; // 每个采样的内存占位
	UInt SoundLength; // 音频buffer长度: data.size / BlockAlign
	UInt TotalTime; // 音频时长: data.size / SampleRate / NumberOfChannels / (BitsPerSample / 8)
};

struct EDGE_DLL AudioSpectrum
{};

NS_EDGE_END

#endif // __AUDIO_COMMON_H_H__