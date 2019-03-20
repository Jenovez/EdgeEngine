/********************************************
名称:CommonConfig 公共配置
说明:
1.
********************************************/

#ifndef __COMMON_CONFIG_H_H__
#define __COMMON_CONFIG_H_H__

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cfloat>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <functional>
#include <algorithm>
#include <fstream>

#ifdef _USEDLL
#define EDGE_DLL _declspec(dllexport)
#else
#define EDGE_DLL _declspec(dllimport)
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef assert
#undef assert
#define assert(expression) (void)(                                                       \
            (!!(expression)) ||                                                              \
            (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \
        )
#endif

#define USING_NS_EDGE using namespace edge
#define NS_EDGE_BEGIN namespace edge {
#define NS_EDGE_END }

#define CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define SAFE_DELETE(p) do { if (p) { delete p; p = NULL; } } while(0);

#ifndef MATH_PI
#define MATH_PI 3.14159
#endif

NS_EDGE_BEGIN

typedef unsigned char Byte;
typedef unsigned int   UInt;
typedef unsigned long ULong;

// 比较两个double值是否相等,相等返回true
static bool equalsDouble(double a, double b)
{
	double temp = a - b;
	if ((temp < -DBL_EPSILON) || (temp > DBL_EPSILON)) { return false; }
	return true;
}

// 比较两个float值是否相等,相等返回true
static bool equalsFloat(float a, float b)
{
	double temp = a - b;
	if ((temp < -FLT_EPSILON) || (temp > FLT_EPSILON)) { return false; }
	return true;
}

// int转换为字符串
static std::string intToString(int num)
{
	char result[32];
	sprintf_s(result, "%d", num);
	return std::string(result);
}

// float转换为字符串
static std::string floatToString(float num)
{
	char result[32];
	sprintf_s(result, "%f", num);
	return std::string(result);
}

// double转换为字符串
static std::string doubleToString(double num)
{
	char result[32];
	sprintf_s(result, "%lf", num);
	return std::string(result);
}

// 字符串转换为int
static int stringToInt(const std::string& str)
{
	return std::atoi(str.c_str());
}

// 字符串转换为long long
static long long stringToLongLong(const std::string& str)
{
	return std::atoll(str.c_str());
}

// 字符串转换为double
static double stringToDouble(const std::string& str)
{
	return std::atof(str.c_str());
}

// 字符串转换为float
static float stringToFloat(const std::string& str)
{
	return (float)stringToDouble(str);
}

/**
* 公用变量
*/
class EDGE_DLL CommonVariable
{
public:
	// 代表错误的数值
	static const int ERROR_NUMBER;
	// 代表错误的字符串
	static const char ERROR_STRING[];
};

// update类型
enum class UpdateType
{
	FAST_UPDATE, // fast update
	NORMAL_UPDATE, // update
	LATE_UPDATE, // late update
	RENDER_UPDATE, // render
};

NS_EDGE_END

#endif // __COMMON_CONFIG_H_H__