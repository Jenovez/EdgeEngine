/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DIRECT3D9_RENDER_CIRCUMSTANCE_H_H__
#define __DIRECT3D9_RENDER_CIRCUMSTANCE_H_H__

#include <renderer/IRenderCircumstance.h>
#include "libd3d9.h"

NS_EDGE_BEGIN

class EDGE_DLL Direct3D9RenderCircumstance final : public IRenderCircumstance
{
public:
	Direct3D9RenderCircumstance();
	~Direct3D9RenderCircumstance();

	bool initRenderer(IWindow* window, const Color& bgColor);

	void beginDraw();
	void endDraw();

public:
	IDirect3DDevice9* getDirect3DDevice9() const;

private:
	IDirect3DDevice9* m_pDevice;

private:
	Color _bgColor;
};

NS_EDGE_END

#endif // __DIRECT3D9_RENDER_CIRCUMSTANCE_H_H__