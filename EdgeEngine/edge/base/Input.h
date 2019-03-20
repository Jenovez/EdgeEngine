/********************************************
名称:
说明:
1.
********************************************/

#ifndef __INPUT_H_H__
#define __INPUT_H_H__

#include <platform/IKeyboard.h>
#include <platform/IMouse.h>

NS_EDGE_BEGIN

class EDGE_DLL Input final
{
public:
	static void init();

	static bool isKeyUp(KeyCode key);
	static bool isKeyDown(KeyCode key);
	static bool isKeyPress(KeyCode key);

	static Vec2 getCurrentPos();

	static bool isLeftDown();
	static bool isRightDown();
	static bool isLeftUp();
	static bool isRightUp();

	static bool isLeftDoubleClick();
	static bool isRightDoubleClick();

private:
	static IKeyboard* _keyboard;
	static IMouse* _mouse;
};

NS_EDGE_END

#endif // __INPUT_H_H__