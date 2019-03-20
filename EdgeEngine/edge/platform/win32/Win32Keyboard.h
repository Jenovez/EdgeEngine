/********************************************
名称:
说明:
1.
********************************************/

#ifndef __WIN32_KEYBOARD_H_H__
#define __WIN32_KEYBOARD_H_H__

#include "libwin32.h"
#include <platform/IKeyboard.h>

NS_EDGE_BEGIN

class EDGE_DLL Win32Keyboard final : public IKeyboard
{
public:
	Win32Keyboard();
	~Win32Keyboard();

	bool isKeyUp(KeyCode key);
	bool isKeyDown(KeyCode key);
	bool isKeyPress(KeyCode key);
	void notifyKeyState(EdgeMessage message, KeyCode key);

private:
	EdgeMessage _message;
	KeyCode _key;
};

NS_EDGE_END

#endif // __WIN32_KEYBOARD_H_H__