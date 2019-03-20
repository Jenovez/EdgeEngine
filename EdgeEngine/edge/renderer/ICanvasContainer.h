/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_CANVAS_CONTAINER_H_H__
#define __I_CANVAS_CONTAINER_H_H__

#include "ITexture2D.h"

NS_EDGE_BEGIN

class EDGE_DLL ICanvasContainer
{
public:
	virtual ~ICanvasContainer() {}

	virtual bool init(const Size& size) = 0;
	virtual ITexture2D* getTexture2D() = 0;

	virtual void setBgColor(const Color& color) = 0;
	virtual const Color& getBgColor() const = 0;
	virtual void beginDraw() = 0;
	virtual void endDraw() = 0;
};

NS_EDGE_END

#endif // __I_CANVAS_CONTAINER_H_H__