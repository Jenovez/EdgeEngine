// cpp文件

#include "Win32PlatformFactory.h"

#include "Win32Keyboard.h"
#include "Win32Mouse.h"
#include "Win32Window.h"

USING_NS_EDGE;

Win32PlatformFactory::Win32PlatformFactory()
{}

Win32PlatformFactory::~Win32PlatformFactory()
{}

IWindow* Win32PlatformFactory::createWindow()
{
	return new Win32Window();
}

IKeyboard* Win32PlatformFactory::createKeyboard()
{
	return new Win32Keyboard();
}

IMouse* Win32PlatformFactory::createMouse()
{
	return new Win32Mouse();
}
