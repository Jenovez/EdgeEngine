/********************************************
名称:
说明:
1.
********************************************/

#ifndef __LIB_XAUDIO2_H_H__
#define __LIB_XAUDIO2_H_H__

#include <Windows.h>
#include <xaudio2.h>
#include <mmsystem.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <mpg123/include/mpg123.h>

#pragma comment(lib, "xaudio2")
#pragma comment(lib, "libvorbisfile")
#pragma comment(lib, "libmpg123")

namespace XAudio2
{
	template<typename Interface>
	inline void SafeRelease(Interface **ppInterfaceToRelease)
	{
		if (*ppInterfaceToRelease != NULL)
		{
			(*ppInterfaceToRelease)->Release();
			(*ppInterfaceToRelease) = NULL;
		}
	}
	template<typename Interface>
	inline void SafeVoiceDestroy(Interface **ppInterfaceToRelease)
	{
		if (*ppInterfaceToRelease != NULL)
		{
			(*ppInterfaceToRelease)->DestroyVoice();
			(*ppInterfaceToRelease) = NULL;
		}
	}
}

#endif // __LIB_XAUDIO2_H_H__