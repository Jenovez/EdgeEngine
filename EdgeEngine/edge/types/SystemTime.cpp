// cpp文件

#include "SystemTime.h"

USING_NS_EDGE;

const SystemTime SystemTime::ZERO;

SystemTime::SystemTime()
: year(0)
, month(0)
, day(0)
, hour(0)
, minute(0)
, second(0)
{}
SystemTime::SystemTime(int year_, int month_, int day_, int hour_, int minute_, int second_)
: year(year_)
, month(month_)
, day(day_)
, hour(hour_)
, minute(minute_)
, second(second_)
{}
SystemTime::SystemTime(const SystemTime& time)
: year(time.year)
, month(time.month)
, day(time.day)
, hour(time.hour)
, minute(time.minute)
, second(time.second)
{}
void SystemTime::setValue(int year, int month, int day, int hour, int minute, int second)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

SystemTime& SystemTime::operator=(const SystemTime& time)
{
	this->year = time.year;
	this->month = time.month;
	this->day = time.day;
	this->hour = time.hour;
	this->minute = time.minute;
	this->second = time.second;
	return *this;
}