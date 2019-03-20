/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_KEYBOARD_H_H__
#define __I_KEYBOARD_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>
#include "PlatformMessage.h"

NS_EDGE_BEGIN

class EDGE_DLL IKeyboard
{
public:
	virtual ~IKeyboard() {}
	
	virtual bool isKeyUp(KeyCode key) = 0;
	virtual bool isKeyDown(KeyCode key) = 0;
	virtual bool isKeyPress(KeyCode key) = 0;

	virtual void notifyKeyState(EdgeMessage message, KeyCode key) = 0;
};

NS_EDGE_END

#endif // __I_KEYBOARD_H_H__