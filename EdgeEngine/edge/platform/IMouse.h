/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_MOUSE_H_H__
#define __I_MOUSE_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>
#include "PlatformMessage.h"

NS_EDGE_BEGIN

class EDGE_DLL IMouse
{
public:
	virtual ~IMouse() {}

	virtual const Vec2& getCurrentPos() const = 0;

	virtual bool isLeftDown() = 0;
	virtual bool isRightDown() = 0;
	virtual bool isLeftUp() = 0;
	virtual bool isRightUp() = 0;

	virtual bool isLeftDoubleClick() = 0;
	virtual bool isRightDoubleClick() = 0;

	virtual void notifyMouseState(EdgeMessage message, const Vec2& pos) = 0;
};

NS_EDGE_END

#endif // __I_MOUSE_H_H__