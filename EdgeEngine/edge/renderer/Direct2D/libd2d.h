/********************************************
名称:
说明:
1.
********************************************/

#ifndef __LIB_D2D_H_H__
#define __LIB_D2D_H_H__

#include <d2d1.h>
#include <wincodec.h>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs")

#ifndef __LIB_DWRITE_H_H__
#define __LIB_DWRITE_H_H__
#include <dwrite.h>
#pragma comment(lib, "dwrite")
#endif // __LIB_DWRITE_H_H__

namespace D2D1
{
	template<typename Interface>
	inline void SafeRelease(Interface **ppInterfaceToRelease)
	{
		if (*ppInterfaceToRelease != NULL)
		{
			(*ppInterfaceToRelease)->Release();

			(*ppInterfaceToRelease) = NULL;
		}
	}
}

#endif // __LIB_D2D_H_H__