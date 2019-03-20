// 实现
#include "Rect.h"
#include "Vector2D.h"
#include "Size.h"

USING_NS_EDGE;

const Rect Rect::ZERO;

Rect::Rect() : left(0.0), right(0.0), top(0.0), bottom(0.0){}
Rect::Rect(double l, double t, double r, double b) : left(l), right(r), top(t), bottom(b){}
Rect::Rect(const Rect& rect) : left(rect.left), right(rect.right), top(rect.top), bottom(rect.bottom){}
Rect::Rect(const Vector2D& posLT, const Size& sizeRB) : left(posLT.x), right(posLT.x + sizeRB.width), top(posLT.y), bottom(posLT.y + sizeRB.height){}

Rect& Rect::operator=(const Rect& rect)
{
	this->left = rect.left;
	this->right = rect.right;
	this->top = rect.top;
	this->bottom = rect.bottom;
	return *this;
}
bool Rect::operator==(const Rect& rect) const { return equals(rect); }
bool Rect::operator!=(const Rect& rect) const { return !equals(rect); }
bool Rect::equals(const Rect& rect) const
{
	if (!equalsDouble(left, rect.left)) { return false; }
	if (!equalsDouble(top, rect.top)) { return false; }
	if (!equalsDouble(right, rect.right)) { return false; }
	if (!equalsDouble(bottom, rect.bottom)) { return false; }
	return true;
}
bool Rect::contains(const Vector2D& vec) const
{
	if (vec.x < left) { return false; }
	if (vec.x > right) { return false; }
	if (vec.y < top) { return false; }
	if (vec.y > bottom) { return false; }
	return true;
}
double Rect::getArea() const
{
	return getWidth() * getHeight();
}
double Rect::getWidth() const
{
	return fabs(right - left);
}
double Rect::getHeight() const
{
	return fabs(bottom - top);
}
void Rect::setValue(double left, double top, double right, double bottom)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}
