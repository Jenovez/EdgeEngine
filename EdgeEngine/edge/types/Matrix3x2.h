/********************************************
名称:
说明:
1.
********************************************/

#ifndef __MATRIX3X2_H_H__
#define __MATRIX3X2_H_H__

#include <base/CommonConfig.h>

NS_EDGE_BEGIN

class Vector2D;

class EDGE_DLL Matrix3x2 final
{
public:
	double _11;
	double _12;
	double _21;
	double _22;
	double _31;
	double _32;

	Matrix3x2(double m11, double m12, double m21, double m22, double m31, double m32);
	Matrix3x2();
	static Matrix3x2 identity();
	bool isIdentity() const;
	void SetProduct(const Matrix3x2 &a, const Matrix3x2 &b);
	Matrix3x2 operator*(const Matrix3x2 &matrix) const;
	void setValue(double m11, double m12, double m21, double m22, double m31, double m32);
};

NS_EDGE_END

#endif // __MATRIX3X2_H_H__