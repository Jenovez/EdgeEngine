/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_AUDIO_CIRCUMSTANCE_H_H__
#define __I_AUDIO_CIRCUMSTANCE_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>
#include <platform/IWindow.h>

NS_EDGE_BEGIN

class EDGE_DLL IAudioCircumstance
{
public:
	virtual ~IAudioCircumstance() {}

	virtual bool initAudio(IWindow* window) = 0;
};

NS_EDGE_END

#endif // __I_AUDIO_CIRCUMSTANCE_H_H__