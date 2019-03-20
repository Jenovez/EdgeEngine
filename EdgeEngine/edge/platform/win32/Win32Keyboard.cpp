// cpp文件

#include "Win32Keyboard.h"

USING_NS_EDGE;

Win32Keyboard::Win32Keyboard()
: _message(EdgeMessage::NONE)
, _key(KeyCode::NONE)
{}
Win32Keyboard::~Win32Keyboard()
{}

int convertToWin32Key(KeyCode key)
{
	int v = 0;
	switch (key)
	{
	case KeyCode::F1: v = VK_F1; break;
	case KeyCode::F2: v = VK_F2; break;
	case KeyCode::F3: v = VK_F3; break;
	case KeyCode::F4: v = VK_F4; break;
	case KeyCode::F5: v = VK_F5; break;
	case KeyCode::F6: v = VK_F6; break;
	case KeyCode::F7: v = VK_F7; break;
	case KeyCode::F8: v = VK_F8; break;
	case KeyCode::F9: v = VK_F9; break;
	case KeyCode::F10: v = VK_F10; break;
	case KeyCode::F11: v = VK_F11; break;
	case KeyCode::F12: v = VK_F12; break;
	case KeyCode::KEY1: v = '1'; break;
	case KeyCode::KEY2: v = '2'; break;
	case KeyCode::KEY3: v = '3'; break;
	case KeyCode::KEY4: v = '4'; break;
	case KeyCode::KEY5: v = '5'; break;
	case KeyCode::KEY6: v = '6'; break;
	case KeyCode::KEY7: v = '7'; break;
	case KeyCode::KEY8: v = '8'; break;
	case KeyCode::KEY9: v = '9'; break;
	case KeyCode::KEY0: v = '0'; break;
	case KeyCode::Q: v = 'Q'; break;
	case KeyCode::W: v = 'W'; break;
	case KeyCode::E: v = 'E'; break;
	case KeyCode::R: v = 'R'; break;
	case KeyCode::T: v = 'T'; break;
	case KeyCode::Y: v = 'Y'; break;
	case KeyCode::U: v = 'U'; break;
	case KeyCode::I: v = 'I'; break;
	case KeyCode::O: v = 'O'; break;
	case KeyCode::P: v = 'P'; break;
	case KeyCode::A: v = 'A'; break;
	case KeyCode::S: v = 'S'; break;
	case KeyCode::D: v = 'D'; break;
	case KeyCode::F: v = 'F'; break;
	case KeyCode::G: v = 'G'; break;
	case KeyCode::H: v = 'H'; break;
	case KeyCode::J: v = 'J'; break;
	case KeyCode::K: v = 'K'; break;
	case KeyCode::L: v = 'L'; break;
	case KeyCode::Z: v = 'Z'; break;
	case KeyCode::X: v = 'X'; break;
	case KeyCode::C: v = 'C'; break;
	case KeyCode::V: v = 'V'; break;
	case KeyCode::B: v = 'B'; break;
	case KeyCode::N: v = 'N'; break;
	case KeyCode::M: v = 'M'; break;
	case KeyCode::ESC:  v = VK_ESCAPE; break;
	case KeyCode::TAB: v = VK_TAB; break;
	case KeyCode::CAPS: v = VK_CAPITAL; break;
	case KeyCode::LSHIFT: v = VK_LSHIFT; break;
	case KeyCode::RSHIFT: v = VK_RSHIFT; break;
	case KeyCode::LCTRL: v = VK_LCONTROL; break;
	case KeyCode::RCTRL: v = VK_RCONTROL; break;
	case KeyCode::LALT: v = VK_LMENU; break;
	case KeyCode::RALT: v = VK_RMENU; break;
	case KeyCode::SPACE: v = VK_SPACE; break;
	case KeyCode::ENTER: v = VK_RETURN; break;
	case KeyCode::BACKSPACE: v = VK_BACK; break;
	case KeyCode::UP: v = VK_UP; break;
	case KeyCode::DOWN: v = VK_DOWN; break;
	case KeyCode::LEFT: v = VK_LEFT; break;
	case KeyCode::RIGHT: v = VK_RIGHT; break;
	case KeyCode::NUM7: v = VK_NUMPAD7; break;
	case KeyCode::NUM8: v = VK_NUMPAD8; break;
	case KeyCode::NUM9: v = VK_NUMPAD9; break;
	case KeyCode::NUM4: v = VK_NUMPAD4; break;
	case KeyCode::NUM5: v = VK_NUMPAD5; break;
	case KeyCode::NUM6: v = VK_NUMPAD6; break;
	case KeyCode::NUM1: v = VK_NUMPAD1; break;
	case KeyCode::NUM2: v = VK_NUMPAD2; break;
	case KeyCode::NUM3: v = VK_NUMPAD3; break;
	case KeyCode::NUM0: v = VK_NUMPAD0; break;
	case KeyCode::NUM_POINT: v = VK_DECIMAL; break;
	case KeyCode::FN_INSERT: v = VK_INSERT; break;
	case KeyCode::FN_HOME: v = VK_HOME; break;
	case KeyCode::FN_PAGEUP: v = VK_PRIOR; break;
	case KeyCode::FN_PAGEDOWN: v = VK_NEXT; break;
	case KeyCode::FN_DELETE: v = VK_DELETE; break;
	case KeyCode::FN_END: v = VK_END; break;
	default: v = 0; break;
	}
	return v;
}

bool Win32Keyboard::isKeyUp(KeyCode key)
{
	if (_key != key) { return false; }
	if (_message != EdgeMessage::KEYUP) { return false; }
	return true;
}

bool Win32Keyboard::isKeyDown(KeyCode key)
{
	if (_key != key) { return false; }
	if (_message != EdgeMessage::KEYDOWN) { return false; }
	return true;
}

bool Win32Keyboard::isKeyPress(KeyCode key)
{
	return GetAsyncKeyState(convertToWin32Key(key)) != 0;
}

void Win32Keyboard::notifyKeyState(EdgeMessage message, KeyCode key)
{
	_message = message;
	_key = key;
}
