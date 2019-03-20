#ifndef __SIZE_H_H__
#define __SIZE_H_H__

#include <base/CommonConfig.h>

NS_EDGE_BEGIN

class Vector2D;

// 表示宽和高
class EDGE_DLL Size final
{
public: // variable
	double width;
	double height;

public: // constant
	static const Size ZERO;

public: // construction functions
	Size();
	Size(double w, double h);
	Size(const Size& size);
	Size(const Vector2D& vec);

public: // operator functions
	Size& operator=(const Size& size);
	Size& operator+=(const Size& size);
	Size& operator-=(const Size& size);
	Size& operator*=(double num);
	Size& operator/=(double num);
	Size& operator*=(const Size& size);
	Size& operator/=(const Size& size);

	Size operator+(const Size& size) const;
	Size operator-(const Size& size) const;
	Size operator*(double num) const;
	Size operator/(double num) const;
	Size operator*(const Size& size) const;
	Size operator/(const Size& size) const;

	bool operator==(const Size& size) const;
	bool operator!=(const Size& size) const;

public: // common use functions
	void setValue(double w, double h);
	bool equals(const Size& size) const;

private: // unable dynamic alloc
	void* operator new(size_t);
	void operator delete(void*);
};

NS_EDGE_END

static edge::Size operator*(double num, const edge::Size& size)
{
	return edge::Size(num * size.width, num * size.height);
}

#endif // __SIZE_H_H__