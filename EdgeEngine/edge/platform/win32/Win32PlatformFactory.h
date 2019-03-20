/********************************************
名称:
说明:
1.
********************************************/

#ifndef __WIN32_PLATFORM_FACTORY_H_H__
#define __WIN32_PLATFORM_FACTORY_H_H__

#include <platform/IPlatformFactory.h>

NS_EDGE_BEGIN

class EDGE_DLL Win32PlatformFactory final : public IPlatformFactory
{
public:
	Win32PlatformFactory();
	~Win32PlatformFactory();

	IWindow* createWindow();
	IKeyboard* createKeyboard();
	IMouse* createMouse();
};

NS_EDGE_END

#endif // __WIN32_PLATFORM_FACTORY_H_H__