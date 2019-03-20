/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT2D_RENDER_CIRCUMSTANCE_H_H__
#define __DIRECT2D_RENDER_CIRCUMSTANCE_H_H__

#include <renderer/IRenderCircumstance.h>
#include "libd2d.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct2DRenderCircumstance final : public IRenderCircumstance
{
public:
	Direct2DRenderCircumstance();
	~Direct2DRenderCircumstance();

	bool initRenderer(IWindow* window, const Color& bgColor);

	void beginDraw();
	void endDraw();

public:
	ID2D1Factory* getID2D1Factory() const;
	ID2D1HwndRenderTarget* getID2D1HwndRenderTarget() const;
	IDWriteFactory* getIDWriteFactory() const;
	IWICImagingFactory* getIWICImagingFactory() const;

private:
	ID2D1Factory* _d2dFactory;
	ID2D1HwndRenderTarget* _d2dRenderTarget;
	IDWriteFactory* _dwFactory;
	IWICImagingFactory* _wicImagingFactory;

private:
	Color _bgColor;
};

NS_EDGE_END

#endif // __DIRECT2D_RENDER_CIRCUMSTANCE_H_H__