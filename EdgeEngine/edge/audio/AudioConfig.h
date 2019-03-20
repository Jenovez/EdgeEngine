/********************************************
名称:
说明:
1.
********************************************/

#ifndef __AUDIO_CONFIG_H_H__
#define __AUDIO_CONFIG_H_H__

#include <platform/PlatformConfig.h>
#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>

NS_EDGE_BEGIN

enum class AUDIO_TYPE
{
	NONE = 0,
	OPENAL = 1,
#if TARGET_PLATFORM == PLATFORM_WIN32
	XAUDIO2 = 9,
#endif
};

NS_EDGE_END

#endif // __AUDIO_CONFIG_H_H__