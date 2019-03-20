// cpp文件

#include "Win32Mouse.h"

USING_NS_EDGE;

Win32Mouse::Win32Mouse()
: _message(EdgeMessage::NONE)
, _currentPos()
{ }
Win32Mouse::~Win32Mouse()
{ }

const Vector2D& Win32Mouse::getCurrentPos() const
{
	return _currentPos;
}

bool Win32Mouse::isLeftDown()
{
	return _message == EdgeMessage::LBUTTONDOWN;
}

bool Win32Mouse::isRightDown()
{
	return _message == EdgeMessage::RBUTTONDOWN;
}

bool Win32Mouse::isLeftUp()
{
	return _message == EdgeMessage::LBUTTONUP;
}

bool Win32Mouse::isRightUp()
{
	return _message == EdgeMessage::RBUTTONUP;
}

bool Win32Mouse::isLeftDoubleClick()
{
	return _message == EdgeMessage::LBUTTONDBCLK;
}

bool Win32Mouse::isRightDoubleClick()
{
	return _message == EdgeMessage::RBUTTONDBCLK;
}

void Win32Mouse::notifyMouseState(EdgeMessage message, const Vec2& pos)
{
	_message = message;

	if (message == EdgeMessage::LBUTTONDBCLK ||
		message == EdgeMessage::LBUTTONDOWN ||
		message == EdgeMessage::LBUTTONUP ||
		message == EdgeMessage::RBUTTONDBCLK ||
		message == EdgeMessage::RBUTTONDOWN ||
		message == EdgeMessage::RBUTTONUP ||
		message == EdgeMessage::MOUSEMOVE)
	{
		_currentPos = pos;
	}
}
