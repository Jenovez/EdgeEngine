/********************************************
名称:
说明:
1.
********************************************/

#ifndef __PLATFORM_MACROS_H_H__
#define __PLATFORM_MACROS_H_H__

//////////////////////////////////////////////////////////////////////////
// pre configure
//////////////////////////////////////////////////////////////////////////

// define supported target platform macro
#define PLATFORM_UNKNOWN 0
#define PLATFORM_WIN32 1
#define PLATFORM_ANDROID 2
#define PLATFORM_IOS 3
#define PLATFORM_MAC 4
#define PLATFORM_LINUX 5

// Determine target platform by compile environment macro.
#define TARGET_PLATFORM             PLATFORM_UNKNOWN

// mac
#if defined(TARGET_OS_MAC) || defined(__APPLE__)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_MAC
#endif

// iphone
#if defined(TARGET_OS_IPHONE)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_IOS
#endif

// android
#if defined(ANDROID)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_ANDROID
#endif

// win32
#if defined(_WIN32) || defined(_WINDOWS)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_WIN32
#endif

// linux
#if defined(LINUX) && !defined(__APPLE__)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_LINUX
#endif

#endif // __PLATFORM_MACROS_H_H__