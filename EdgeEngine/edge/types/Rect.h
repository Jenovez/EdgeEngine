#ifndef __RECT_H_H__
#define __RECT_H_H__

#include <base/CommonConfig.h>

NS_EDGE_BEGIN

class Vector2D;
class Size;

// 表示矩形
class EDGE_DLL Rect final
{
public: // variable
	double left;
	double right;
	double top;
	double bottom;

public: // constant
	static const Rect ZERO;

public: // construction functions
	Rect();
	Rect(const Rect& rect);
	Rect(double left, double top, double right, double bottom);
	/**
	*	param1:left & top variable
	*	param2:right & bottom variable
	*/
	Rect(const Vector2D& posLT, const Size& sizeRB);

public: // operator functions
	Rect& operator=(const Rect& rect);

	bool operator==(const Rect& rect) const;
	bool operator!=(const Rect& rect) const;

public: // common use functions
	bool equals(const Rect& rect) const;
	bool contains(const Vector2D& vec) const;

	double getArea() const;
	double getWidth() const;
	double getHeight() const;

	void setValue(double left, double top, double right, double bottom);

private: // unable dynamic alloc
	void* operator new(size_t);
	void operator delete(void*);
};

NS_EDGE_END

#endif // __RECT_H_H__