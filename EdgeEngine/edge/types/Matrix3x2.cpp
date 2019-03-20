// cpp文件

#include "Matrix3x2.h"
#include "Vector2D.h"

USING_NS_EDGE;

Matrix3x2::Matrix3x2(double m11, double m12, double m21, double m22, double m31, double m32)
: _11(m11)
, _12(m12)
, _21(m21)
, _22(m22)
, _31(m31)
, _32(m32)
{}

Matrix3x2::Matrix3x2()
: _11(1.0)
, _12(0.0)
, _21(0.0)
, _22(1.0)
, _31(0.0)
, _32(0.0)
{}

Matrix3x2 Matrix3x2::identity()
{
	return Matrix3x2(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
}

bool Matrix3x2::isIdentity() const
{
	return     _11 == 1.0 && _12 == 0.0
		&& _21 == 0.0 && _22 == 1.0
		&& _31 == 0.0 && _32 == 0.0;
}

void Matrix3x2::SetProduct(const Matrix3x2 &a, const Matrix3x2 &b)
{
	_11 = a._11 * b._11 + a._12 * b._21;
	_12 = a._11 * b._12 + a._12 * b._22;
	_21 = a._21 * b._11 + a._22 * b._21;
	_22 = a._21 * b._12 + a._22 * b._22;
	_31 = a._31 * b._11 + a._32 * b._21 + b._31;
	_32 = a._31 * b._12 + a._32 * b._22 + b._32;
}

Matrix3x2 Matrix3x2::operator*(const Matrix3x2 &matrix) const
{
	Matrix3x2 result;

	result.SetProduct(*this, matrix);

	return result;
}

void Matrix3x2::setValue(double m11, double m12, double m21, double m22, double m31, double m32)
{
	_11 = m11;
	_12 = m12;
	_21 = m21;
	_22 = m22;
	_31 = m31;
	_32 = m32;
}
