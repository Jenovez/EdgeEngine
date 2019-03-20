/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_PLATFORM_FACOTRY_H_H__
#define __I_PLATFORM_FACOTRY_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>

NS_EDGE_BEGIN

class IWindow;
class IKeyboard;
class IMouse;

class EDGE_DLL IPlatformFactory
{
public:
	virtual ~IPlatformFactory() {}

	virtual IWindow* createWindow() = 0;
	virtual IKeyboard* createKeyboard() = 0;
	virtual IMouse* createMouse() = 0;
};

NS_EDGE_END

#endif // __I_PLATFORM_FACOTRY_H_H__