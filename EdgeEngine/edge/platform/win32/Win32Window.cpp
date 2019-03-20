// cpp文件

#include "Win32Window.h"

USING_NS_EDGE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

Win32Window::Win32Window()
: _hwnd(NULL)
, _hInstance(NULL)
, _clientSize(Size::ZERO)
, _wndSize(Size::ZERO)
, _desktopSize(Size::ZERO)
, m_sTitle("")
, m_sWndClassName("")
, _windowPos(Vec2::ZERO)
, _windowMessage(EdgeMessage::NONE)
, _sysTime(SystemTime::ZERO)
, m_bFullScreen(false)
, m_bShowConsole(true)
{
	showConsole(false);
	updateTime();

	CoInitialize(NULL);
}

Win32Window::~Win32Window()
{
	if (_hwnd)
	{
		UnregisterClass(m_sWndClassName.c_str(), _hInstance);
	}
	CoUninitialize();
}

bool Win32Window::initWindow(bool bFullScreen, const std::string& title, const Size& clientSize)
{
	_hInstance = GetModuleHandle(NULL);

	m_sTitle = title;

	WNDCLASSEX wnd;
	ZeroMemory(&wnd, sizeof(WNDCLASSEX));
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hInstance = _hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_sWndClassName = title + "ClassName";
	wnd.lpszClassName = m_sWndClassName.c_str();
	ATOM rce = RegisterClassEx(&wnd);
	assert(rce != NULL);
	if (rce == NULL) { return false; }

	_desktopSize.setValue(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

	if (bFullScreen)
	{
		_hwnd = CreateWindow(
			wnd.lpszClassName, title.c_str(),
			WS_POPUP,
			0, 0, (int)_desktopSize.width, (int)_desktopSize.height,
			NULL, NULL, _hInstance, NULL);
		assert(_hwnd != NULL);
		if (_hwnd == NULL)
		{
			UnregisterClass(wnd.lpszClassName, _hInstance);
			return false;
		}

		_clientSize = _desktopSize;
	}
	else
	{
		_hwnd = CreateWindow(
			wnd.lpszClassName, title.c_str(),
			WS_SYSMENU | WS_POPUP | WS_CAPTION,
			0, 0, (int)clientSize.width, (int)clientSize.height,
			NULL, NULL, _hInstance, NULL);
		assert(_hwnd != NULL);
		if (_hwnd == NULL)
		{
			UnregisterClass(wnd.lpszClassName, _hInstance);
			return false;
		}

		RECT tempRc;
		GetClientRect(_hwnd, &tempRc);
		_wndSize.width = clientSize.width * 2 - (tempRc.right - tempRc.left);
		_wndSize.height = clientSize.height * 2 - (tempRc.bottom - tempRc.top);

		Vec2 startPos = (_desktopSize - _wndSize) / 2.0;

		MoveWindow(_hwnd, (int)startPos.x, (int)startPos.y, (int)_wndSize.width, (int)_wndSize.height, TRUE);

		GetClientRect(_hwnd, &tempRc);
		_clientSize.setValue((int)(tempRc.right - tempRc.left), (int)(tempRc.bottom - tempRc.top));
	}

	ShowWindow(_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(_hwnd);

	return true;
}

bool Win32Window::changeDisplay(bool fullscreen, const Size& clientSize)
{
	return true;
}

bool Win32Window::isFullScreen() const { return m_bFullScreen; }
const Size& Win32Window::getClientSize() const { return _clientSize; }
const Size& Win32Window::getDesktopSize() const { return _desktopSize; }

void Win32Window::setTitle(const std::string& title)
{
	SetWindowText(_hwnd, title.c_str());
}

const std::string& Win32Window::getTitle() const { return m_sTitle; }

void Win32Window::setWindowPos(const Vec2& pos)
{
	MoveWindow(_hwnd, (int)pos.x, (int)pos.y, (int)_wndSize.width, (int)_wndSize.height, TRUE);
}

const Vec2& Win32Window::getWindowPos()
{
	RECT tempRc;
	GetWindowRect(_hwnd, &tempRc);
	_windowPos.setValue(tempRc.left, tempRc.top);
	return _windowPos;
}

void Win32Window::showWindow(bool enable)
{
	int bShow = (enable ? SW_SHOWDEFAULT : SW_HIDE);
	ShowWindow(_hwnd, bShow);
}

void Win32Window::showConsole(bool enable)
{
	if (m_bShowConsole != enable)
	{
		m_bShowConsole = enable;

		if (m_bShowConsole)
		{
			AllocConsole();
		}
		else
		{
			FreeConsole();
		}
	}
}

void Win32Window::showCursor(bool enable)
{
	ShowCursor((BOOL)enable);
}

void Win32Window::update(IKeyboard* keyboard, IMouse* mouse)
{
	_windowMessage = EdgeMessage::NONE;
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		switch (msg.message)
		{
		case WM_QUIT:
			_windowMessage = EdgeMessage::QUIT;
			break;
		case WM_KEYDOWN:
			_windowMessage = EdgeMessage::KEYDOWN;
			break;
		case WM_KEYUP:
			_windowMessage = EdgeMessage::KEYUP;
			break;
		case WM_LBUTTONDOWN:
			_windowMessage = EdgeMessage::LBUTTONDOWN;
			break;
		case WM_RBUTTONDOWN:
			_windowMessage = EdgeMessage::RBUTTONDOWN;
			break;
		case WM_LBUTTONUP:
			_windowMessage = EdgeMessage::LBUTTONUP;
			break;
		case WM_RBUTTONUP:
			_windowMessage = EdgeMessage::RBUTTONUP;
			break;
		case WM_LBUTTONDBLCLK:
			_windowMessage = EdgeMessage::LBUTTONDBCLK;
			break;
		case WM_RBUTTONDBLCLK:
			_windowMessage = EdgeMessage::RBUTTONDBCLK;
			break;
		case WM_MOUSEMOVE:
			_windowMessage = EdgeMessage::MOUSEMOVE;
			break;
		}
	}

	KeyCode keycode;
	switch (msg.wParam)
	{
	case VK_F1: keycode = KeyCode::F1; break;
	case VK_F2: keycode = KeyCode::F2; break;
	case VK_F3: keycode = KeyCode::F3; break;
	case VK_F4: keycode = KeyCode::F4; break;
	case VK_F5: keycode = KeyCode::F5; break;
	case VK_F6: keycode = KeyCode::F6; break;
	case VK_F7: keycode = KeyCode::F7; break;
	case VK_F8: keycode = KeyCode::F8; break;
	case VK_F9: keycode = KeyCode::F9; break;
	case VK_F10: keycode = KeyCode::F10; break;
	case VK_F11: keycode = KeyCode::F11; break;
	case VK_F12: keycode = KeyCode::F12; break;
	case '1': keycode = KeyCode::KEY1; break;
	case '2': keycode = KeyCode::KEY2; break;
	case '3': keycode = KeyCode::KEY3; break;
	case '4': keycode = KeyCode::KEY4; break;
	case '5': keycode = KeyCode::KEY5; break;
	case '6': keycode = KeyCode::KEY6; break;
	case '7': keycode = KeyCode::KEY7; break;
	case '8': keycode = KeyCode::KEY8; break;
	case '9': keycode = KeyCode::KEY9; break;
	case '0': keycode = KeyCode::KEY0; break;
	case 'A': keycode = KeyCode::A; break;
	case 'B': keycode = KeyCode::B; break;
	case 'C': keycode = KeyCode::C; break;
	case 'D': keycode = KeyCode::D; break;
	case 'E': keycode = KeyCode::E; break;
	case 'F': keycode = KeyCode::F; break;
	case 'G': keycode = KeyCode::G; break;
	case 'H': keycode = KeyCode::H; break;
	case 'I': keycode = KeyCode::I; break;
	case 'J': keycode = KeyCode::J; break;
	case 'K': keycode = KeyCode::K; break;
	case 'L': keycode = KeyCode::L; break;
	case 'M': keycode = KeyCode::M; break;
	case 'N': keycode = KeyCode::N; break;
	case 'O': keycode = KeyCode::O; break;
	case 'P': keycode = KeyCode::P; break;
	case 'Q': keycode = KeyCode::Q; break;
	case 'R': keycode = KeyCode::R; break;
	case 'S': keycode = KeyCode::S; break;
	case 'T': keycode = KeyCode::T; break;
	case 'U': keycode = KeyCode::U; break;
	case 'V': keycode = KeyCode::V; break;
	case 'W': keycode = KeyCode::W; break;
	case 'X': keycode = KeyCode::X; break;
	case 'Y': keycode = KeyCode::Y; break;
	case 'Z': keycode = KeyCode::Z; break;
	case VK_ESCAPE: keycode = KeyCode::ESC; break;
	case VK_TAB: keycode = KeyCode::TAB; break;
	case VK_CAPITAL: keycode = KeyCode::CAPS; break;
	case VK_LSHIFT: keycode = KeyCode::LSHIFT; break;
	case VK_RSHIFT: keycode = KeyCode::RSHIFT; break;
	case VK_LCONTROL: keycode = KeyCode::LCTRL; break;
	case VK_RCONTROL: keycode = KeyCode::RCTRL; break;
	case VK_LMENU: keycode = KeyCode::LALT; break;
	case VK_RMENU: keycode = KeyCode::RALT; break;
	case VK_SPACE: keycode = KeyCode::SPACE; break;
	case VK_RETURN: keycode = KeyCode::ENTER; break;
	case VK_BACK: keycode = KeyCode::BACKSPACE; break;
	case VK_UP: keycode = KeyCode::UP; break;
	case VK_DOWN: keycode = KeyCode::DOWN; break;
	case VK_LEFT: keycode = KeyCode::LEFT; break;
	case VK_RIGHT: keycode = KeyCode::RIGHT; break;
	case VK_NUMPAD7: keycode = KeyCode::NUM7; break;
	case VK_NUMPAD8: keycode = KeyCode::NUM8; break;
	case VK_NUMPAD9: keycode = KeyCode::NUM9; break;
	case VK_NUMPAD4: keycode = KeyCode::NUM4; break;
	case VK_NUMPAD5: keycode = KeyCode::NUM5; break;
	case VK_NUMPAD6: keycode = KeyCode::NUM6; break;
	case VK_NUMPAD1: keycode = KeyCode::NUM1; break;
	case VK_NUMPAD2: keycode = KeyCode::NUM2; break;
	case VK_NUMPAD3: keycode = KeyCode::NUM3; break;
	case VK_NUMPAD0: keycode = KeyCode::NUM0; break;
	case VK_DECIMAL: keycode = KeyCode::NUM_POINT; break;
	case VK_INSERT: keycode = KeyCode::FN_INSERT; break;
	case VK_HOME: keycode = KeyCode::FN_HOME; break;
	case VK_PRIOR: keycode = KeyCode::FN_PAGEUP; break;
	case VK_NEXT: keycode = KeyCode::FN_PAGEDOWN; break;
	case VK_DELETE: keycode = KeyCode::FN_DELETE; break;
	case VK_END: keycode = KeyCode::FN_END; break;
	default: keycode = KeyCode::NONE; break;
	}
	keyboard->notifyKeyState(_windowMessage, keycode);
	mouse->notifyMouseState(_windowMessage, Vec2(LOWORD(msg.lParam), HIWORD(msg.lParam)));

	updateTime();
}

const EdgeMessage& Win32Window::getCurrentMessage() const { return _windowMessage; }

void Win32Window::sleep(UInt millionSecond)
{
	Sleep(millionSecond);
}

ULong Win32Window::getTickCount()
{
	return (ULong)timeGetTime();
}
const SystemTime& Win32Window::getSystemTime() const { return _sysTime; }

HWND Win32Window::getHWND() const { return _hwnd; }
HINSTANCE Win32Window::getHInstance() const { return _hInstance; }
const std::string& Win32Window::getWindowClassName() const { return m_sWndClassName; }

void Win32Window::updateTime()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	_sysTime.setValue(
		time.wYear, time.wMonth, time.wDay, // yy-mm-dd
		time.wHour, time.wMinute, time.wSecond); // hh-mm-ss
}
