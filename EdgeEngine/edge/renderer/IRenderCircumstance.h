/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_RENDER_CIRCUMSTANCE_H_H__
#define __I_RENDER_CIRCUMSTANCE_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>
#include <platform/IWindow.h>

NS_EDGE_BEGIN

class EDGE_DLL IRenderCircumstance
{
public:
	virtual ~IRenderCircumstance() {}

	virtual bool initRenderer(IWindow* window, const Color& bgColor) = 0;

	virtual void beginDraw() = 0;
	virtual void endDraw() = 0;

private:

};

NS_EDGE_END

#endif // __I_RENDER_CIRCUMSTANCE_H_H__