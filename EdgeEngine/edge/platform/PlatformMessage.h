/********************************************
名称:
说明:
1.
********************************************/

#ifndef __PLATFORM_MESSAGE_H_H__
#define __PLATFORM_MESSAGE_H_H__

#include <base/CommonConfig.h>

NS_EDGE_BEGIN

enum class EdgeMessage
{
	NONE = 0,
	QUIT,
	KEYDOWN,
	KEYUP,
	LBUTTONDOWN,
	RBUTTONDOWN,
	LBUTTONUP,
	RBUTTONUP,
	LBUTTONDBCLK,
	RBUTTONDBCLK,
	MOUSEMOVE,
};

enum class KeyCode
{
	NONE = 0,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	KEY1, KEY2, KEY3, KEY4, KEY5, KEY6, KEY7, KEY8, KEY9, KEY0,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	ESC, TAB, CAPS,
	LSHIFT, RSHIFT,
	LCTRL, RCTRL,
	LALT, RALT,
	SPACE, ENTER,
	BACKSPACE,
	UP, DOWN, LEFT, RIGHT,
	NUM7, NUM8, NUM9,
	NUM4, NUM5, NUM6,
	NUM1, NUM2, NUM3,
	NUM0, NUM_POINT,
	FN_INSERT, FN_HOME, FN_PAGEUP,
	FN_DELETE, FN_END, FN_PAGEDOWN
};

NS_EDGE_END

#endif // __PLATFORM_MESSAGE_H_H__