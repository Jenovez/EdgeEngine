// 实现

#include "Vector2D.h"
#include "Size.h"

USING_NS_EDGE;

const Vector2D Vector2D::ZERO;

Vector2D::Vector2D() : x(0.0), y(0.0) {}
Vector2D::Vector2D(double a, double b) : x(a), y(b) {}
Vector2D::Vector2D(const Vector2D& vec) : x(vec.x), y(vec.y) {}
Vector2D::Vector2D(const Size& size) : x(size.width), y(size.height) {}

Vector2D& Vector2D::operator=(const Vector2D& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return *this;
}
Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}
Vector2D& Vector2D::operator*=(double num)
{
	this->x *= num;
	this->y *= num;
	return *this;
}
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	assert(vec != Vector2D::ZERO);
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}
Vector2D& Vector2D::operator/=(double num)
{
	assert(!equalsDouble(num, 0.0));
	this->x /= num;
	this->y /= num;
	return *this;
}
Vector2D Vector2D::operator+(const Vector2D& vec) const
{
	return Vector2D(this->x + vec.x, this->y + vec.y);
}
Vector2D Vector2D::operator-(const Vector2D& vec) const
{
	return Vector2D(this->x - vec.x, this->y - vec.y);
}
Vector2D Vector2D::operator*(const Vector2D& vec) const
{
	return Vector2D(this->x * vec.x, this->y * vec.y);
}
Vector2D Vector2D::operator*(double num) const
{
	return Vector2D(this->x * num, this->y * num);
}
Vector2D Vector2D::operator/(const Vector2D& vec) const
{
	assert(vec != Vector2D::ZERO);
	return Vector2D(this->x / vec.x, this->y / vec.y);
}
Vector2D Vector2D::operator/(double num) const
{
	assert(!equalsDouble(num, 0.0));
	return Vector2D(this->x / num, this->y / num);
}
bool Vector2D::operator==(const Vector2D& vec) const { return equals(vec); }
bool Vector2D::operator!=(const Vector2D& vec) const { return !equals(vec); }
double Vector2D::length() const
{
	return sqrt(x * x + y * y);
}
double Vector2D::distance(const Vector2D& vec) const
{
	double dx = vec.x - this->x;
	double dy = vec.y - this->y;
	return sqrt(dx * dx + dy * dy);
}
bool Vector2D::equals(const Vector2D& vec) const
{
	if (!equalsDouble(this->x, vec.x)) { return false; }
	if (!equalsDouble(this->y, vec.y)) { return false; }
	return true;
}
Vector2D Vector2D::getNormalize() const
{
	Vector2D vec(*this);
	vec.toNormalize();
	return vec;
}
void Vector2D::toNormalize()
{
	double n = x * x + y * y;
	// Already normalized.
	if (equalsDouble(n, 1.0)) { return; }
	if (equalsDouble(n, 0.0)) { return; }

	n = sqrt(n);
	// Too close to zero.
	if (equalsDouble(n, 0.0)) { return; }

	n = 1.0 / n;
	x *= n;
	y *= n;
}
void Vector2D::setValue(double x, double y)
{
	this->x = x;
	this->y = y;
}
