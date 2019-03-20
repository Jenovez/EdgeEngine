// cpp文件

#include "Input.h"
#include <platform/PlatformManager.h>

USING_NS_EDGE;

void Input::init()
{
	_keyboard = PlatformManager::getInstance()->getKeyboard();
	_mouse = PlatformManager::getInstance()->getMouse();
}

bool Input::isKeyUp(KeyCode key)
{
	return _keyboard->isKeyUp(key);
}

bool Input::isKeyDown(KeyCode key)
{
	return _keyboard->isKeyDown(key);
}

bool Input::isKeyPress(KeyCode key)
{
	return _keyboard->isKeyPress(key);
}

Vec2 Input::getCurrentPos()
{
	return _mouse->getCurrentPos();
}

bool Input::isLeftDown()
{
	return _mouse->isLeftDown();
}

bool Input::isRightDown()
{
	return _mouse->isRightDown();
}

bool Input::isLeftUp()
{
	return _mouse->isLeftUp();
}

bool Input::isRightUp()
{
	return _mouse->isRightUp();
}

bool Input::isLeftDoubleClick()
{
	return _mouse->isLeftDoubleClick();
}

bool Input::isRightDoubleClick()
{
	return _mouse->isRightDoubleClick();
}

IKeyboard* Input::_keyboard = NULL;
IMouse* Input::_mouse = NULL;