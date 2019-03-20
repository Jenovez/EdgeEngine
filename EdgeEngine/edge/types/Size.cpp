// 实现
#include "Size.h"
#include "Vector2D.h"

USING_NS_EDGE;

const Size Size::ZERO;

Size::Size() : width(0.0), height(0.0) {}
Size::Size(double w, double h) : width(w), height(h) {}
Size::Size(const Size& size) : width(size.width), height(size.height) {}
Size::Size(const Vector2D& vec) : width(vec.x), height(vec.y) {}

Size& Size::operator=(const Size& size)
{
	this->width = size.width;
	this->height = size.height;
	return *this;
}
Size& Size::operator+=(const Size& size)
{
	this->width += size.width;
	this->height += size.height;
	return *this;
}
Size& Size::operator-=(const Size& size)
{
	this->width -= size.width;
	this->height -= size.height;
	return *this;
}
Size& Size::operator*=(double num)
{
	this->width *= num;
	this->height *= num;
	return *this;
}
Size& Size::operator/=(double num)
{
	assert(!equalsDouble(num, 0.0));
	this->width /= num;
	this->height /= num;
	return *this;
}
Size& Size::operator*=(const Size& size)
{
	this->width *= size.width;
	this->height *= size.height;
	return *this;
}
Size& Size::operator/=(const Size& size)
{
	assert(size != Size::ZERO);
	this->width /= size.width;
	this->height /= size.height;
	return *this;
}
Size Size::operator+(const Size& size) const
{
	return Size(this->width + size.width, this->height + size.height);
}
Size Size::operator-(const Size& size) const
{
	return Size(this->width - size.width, this->height - size.height);
}
Size Size::operator*(double num) const
{
	return Size(num * this->width, num * this->height);
}
Size Size::operator/(double num) const
{
	assert(!equalsDouble(num, 0.0));
	return Size(this->width / num, this->height / num);
}
Size Size::operator*(const Size& size) const
{
	return Size(this->width * size.width, this->height * size.height);
}
Size Size::operator/(const Size& size) const
{
	assert(size != Size::ZERO);
	return Size(this->width / size.width, this->height / size.height);
}
bool Size::operator==(const Size& size) const { return equals(size); }
bool Size::operator!=(const Size& size) const { return !equals(size); }
void Size::setValue(double w, double h)
{
	this->width = w;
	this->height = h;
}
bool Size::equals(const Size& size) const
{
	if (!equalsDouble(this->width, size.width)) { return false; }
	if (!equalsDouble(this->height, size.height)) { return false; }
	return true;
}