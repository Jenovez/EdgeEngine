/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_WINDOW_H_H__
#define __I_WINDOW_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>
#include "PlatformMessage.h"

#include "IKeyboard.h"
#include "IMouse.h"

NS_EDGE_BEGIN

class EDGE_DLL IWindow
{
public:
	virtual ~IWindow() {}

	virtual bool initWindow(bool bFullScreen, const std::string& title, const Size& clientSize) = 0;

	virtual bool changeDisplay(bool bFullScreen, const Size& clientSize) = 0;
	virtual bool isFullScreen() const = 0;
	virtual const Size& getClientSize() const = 0;
	virtual const Size& getDesktopSize() const = 0;

	virtual void setTitle(const std::string& title) = 0;
	virtual const std::string& getTitle() const = 0;

	virtual void setWindowPos(const Vec2& pos) = 0;
	virtual const Vec2& getWindowPos() = 0;

	virtual void showWindow(bool enable) = 0;
	virtual void showConsole(bool enable) = 0;
	virtual void showCursor(bool enable) = 0;

	virtual void update(IKeyboard* keyboard, IMouse* mouse) = 0;
	virtual const EdgeMessage& getCurrentMessage() const = 0;
	virtual void sleep(UInt millionSecond) = 0;
	virtual ULong getTickCount() = 0;
	virtual const SystemTime& getSystemTime() const = 0;
};

NS_EDGE_END

#endif // __I_WINDOW_H_H__