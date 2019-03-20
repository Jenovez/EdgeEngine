/********************************************
名称:
说明:
1.
********************************************/

#ifndef __RENDERER_CONFIG_H_H__
#define __RENDERER_CONFIG_H_H__

#include <base/CommonConfig.h>
#include <platform/PlatformConfig.h>

NS_EDGE_BEGIN

enum class RENDERER_TYPE
{
	NONE = 0,
	OPENGL = 1, // OpenGL
	OPENGLES = 2, // OpenGL ES
#if TARGET_PLATFORM == PLATFORM_WIN32
	DIRECT2D = 3, // Direct2D
	DIRECT3D9 = 4, // Direct3D v9
	DIRECT3D11 = 5, // Direct3D v11
	GDI = 6, // GDI
#endif
};

NS_EDGE_END

#endif // __RENDERER_CONFIG_H_H__