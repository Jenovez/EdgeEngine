/********************************************
名称:
说明:
1.
********************************************/

#ifndef __WIN32_WINDOW_H_H__
#define __WIN32_WINDOW_H_H__

#include "libwin32.h"
#include <platform/IWindow.h>

NS_EDGE_BEGIN

class Win32Window final : public IWindow
{
public: // Implements From IWindow
	Win32Window();
	~Win32Window();

	bool initWindow(bool bFullScreen, const std::string& title, const Size& clientSize);

	bool changeDisplay(bool bFullScreen, const Size& clientSize);
	bool isFullScreen() const;
	const Size& getClientSize() const;
	const Size& getDesktopSize() const;

	void setTitle(const std::string& title);
	const std::string& getTitle() const;

	void setWindowPos(const Vec2& pos);
	const Vec2& getWindowPos();

	void showWindow(bool enable);
	void showConsole(bool enable);
	void showCursor(bool enable);

	void update(IKeyboard* keyboard, IMouse* mouse);
	const EdgeMessage& getCurrentMessage() const;
	void sleep(UInt millionSecond);
	ULong getTickCount();
	const SystemTime& getSystemTime() const;

public: // win32
	HWND getHWND() const;
	HINSTANCE getHInstance() const;
	const std::string& getWindowClassName() const;

private:
	void updateTime();

private:
	HWND _hwnd;
	HINSTANCE _hInstance;

	Size _clientSize;
	Size _wndSize;
	Size _desktopSize;
	std::string m_sTitle;
	std::string m_sWndClassName;
	Vec2 _windowPos;

	EdgeMessage _windowMessage;
	SystemTime _sysTime;

	bool m_bFullScreen;
	bool m_bShowConsole;
};

NS_EDGE_END

#endif // __WIN32_WINDOW_H_H__