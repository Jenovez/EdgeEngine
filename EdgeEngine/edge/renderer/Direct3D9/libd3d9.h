/********************************************
名称:
说明:
1.
********************************************/

#ifndef __LIB_D3D_H_H__
#define __LIB_D3D_H_H__

#include <d3dx9/include/d3d9.h>
#include <d3dx9/include/d3dx9.h>

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

//#ifndef __LIB_DWRITE_H_H__
//#define __LIB_DWRITE_H_H__
//#include <dwrite.h>
//#pragma comment(lib, "dwrite")
//#endif // __LIB_DWRITE_H_H__

namespace D3D9
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

#endif // __LIB_D3D_H_H__