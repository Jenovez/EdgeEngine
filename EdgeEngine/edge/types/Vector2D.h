#ifndef __VECTOR2D_H_H__
#define __VECTOR2D_H_H__

#include <base/CommonConfig.h>

NS_EDGE_BEGIN

class Size;

// 二维向量
class EDGE_DLL Vector2D final
{
public: // variable
	double x;
	double y;

public: // constant
	static const Vector2D ZERO;

public: // construction
	Vector2D();
	Vector2D(double x, double y);
	Vector2D(const Vector2D& vec);
	Vector2D(const Size& size);

public: // operator functions
	Vector2D& operator=(const Vector2D& vec);
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator*=(double num);
	Vector2D& operator/=(const Vector2D& vec);
	Vector2D& operator/=(double num);

	Vector2D operator+(const Vector2D& vec) const;
	Vector2D operator-(const Vector2D& vec) const;
	Vector2D operator*(const Vector2D& vec) const;
	Vector2D operator*(double num) const;
	Vector2D operator/(const Vector2D& vec) const;
	Vector2D operator/(double num) const;

	bool operator==(const Vector2D& vec) const;
	bool operator!=(const Vector2D& vec) const;

public: // common use functions
	double length() const;
	double distance(const Vector2D& vec) const;
	bool equals(const Vector2D& vec) const;
	Vector2D getNormalize() const;
	void toNormalize();
	void setValue(double x, double y);

private: // unable dynamic alloc
	void* operator new(size_t);
	void operator delete(void*);

} typedef Vec2, Point2D;

NS_EDGE_END

static edge::Vector2D operator*(double num, const edge::Vector2D& vec)
{
	return edge::Vector2D(num * vec.x, num * vec.y);
}

#endif // __VECTOR2D_H_H__