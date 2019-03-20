/********************************************
名称:系统时间
说明:
1.
********************************************/

#ifndef __SYSTEM_TIME_H_H__
#define __SYSTEM_TIME_H_H__

#include <base/CommonConfig.h>

NS_EDGE_BEGIN

class EDGE_DLL SystemTime final
{
public:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public: // constant
	static const SystemTime ZERO;

public: // construction functions
	explicit SystemTime();
	explicit SystemTime(int year, int month, int day, int hour, int minute, int second);
	SystemTime(const SystemTime& time);

public: // operator functions
	SystemTime& operator=(const SystemTime& time);

private: // unable dynamic alloc
	void* operator new(size_t);
	void operator delete(void*);

public:
	void setValue(int year, int month, int day, int hour, int minute, int second);
};

NS_EDGE_END

#endif // __SYSTEM_TIME_H_H__