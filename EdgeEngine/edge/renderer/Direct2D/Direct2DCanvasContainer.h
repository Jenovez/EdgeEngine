/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT2D_CANVAS_CONTAINER_H_H__
#define __DIRECT2D_CANVAS_CONTAINER_H_H__

#include <renderer/ICanvasContainer.h>
#include "libd2d.h"

NS_EDGE_BEGIN

class Direct2DRenderCircumstance;
class Direct2DTexture2D;

class EDGE_DLL Direct2DCanvasContainer final : public ICanvasContainer
{
public:
	Direct2DCanvasContainer(Direct2DRenderCircumstance* circumstance);
	~Direct2DCanvasContainer();

	bool init(const Size& size);

	ITexture2D* getTexture2D();

	void setBgColor(const Color& color);
	const Color& getBgColor() const;

	void beginDraw();
	void endDraw();

public:
	Direct2DRenderCircumstance* getRenderCircumstance() const;
	ID2D1BitmapRenderTarget* getID2D1BitmapRenderTarget() const;

private:
	Direct2DRenderCircumstance* _d2dRC;

	ID2D1BitmapRenderTarget* _renderRT;
	Direct2DTexture2D* _texture2d;
	Color _bgColor;
};

NS_EDGE_END

#endif // __DIRECT2D_CANVAS_CONTAINER_H_H__