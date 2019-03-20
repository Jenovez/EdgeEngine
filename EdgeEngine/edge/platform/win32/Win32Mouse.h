/********************************************
名称:
说明:
1.
********************************************/

#ifndef __WIN32_MOUSE_H_H__
#define __WIN32_MOUSE_H_H__

#include "libwin32.h"
#include <platform/IMouse.h>

NS_EDGE_BEGIN

class EDGE_DLL Win32Mouse final : public IMouse
{
public:
	Win32Mouse();
	~Win32Mouse();

	const Vec2& getCurrentPos() const;
	bool isLeftDown();
	bool isRightDown();
	bool isLeftUp();
	bool isRightUp();
	bool isLeftDoubleClick();
	bool isRightDoubleClick();
	void notifyMouseState(EdgeMessage message, const Vec2& pos);

private:
	EdgeMessage _message;
	Vector2D _currentPos;
};

NS_EDGE_END

#endif // __WIN32_MOUSE_H_H__