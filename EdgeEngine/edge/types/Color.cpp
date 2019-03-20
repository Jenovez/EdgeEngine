// 实现
#include "Color.h"

USING_NS_EDGE;

float floatToByteAnd(float dest1, float dest2) { return (float)((Byte)(dest1 * 255.0f) & (Byte)(dest2 * 255.0)) / 255.0f; }
float floatToByteOr(float dest1, float dest2) { return (float)((Byte)(dest1 * 255.0f) | (Byte)(dest2 * 255.0)) / 255.0f; }
float floatToByteNor(float dest1, float dest2) { return (float)((Byte)(dest1 * 255.0f) ^ (Byte)(dest2 * 255.0)) / 255.0f; }
float floatToByteBack(float dest) { return (float)~((Byte)(dest * 255.0f)); }

const Color Color::ZERO(0, 0, 0, 0);
const Color Color::WHITE(1, 1, 1, 1);
const Color Color::BLACK(0, 0, 0, 1);
const Color Color::RED(1, 0, 0, 1);
const Color Color::GREEN(0, 1, 0, 1);
const Color Color::BLUE(0, 0, 1, 1);

Color::Color() : r(1), g(1), b(1), a(1) {}
Color::Color(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}
Color::Color(const Color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

Color& Color::operator&=(const Color& color)
{
	this->r = floatToByteAnd(this->r, color.r);
	this->g = floatToByteAnd(this->g, color.g);
	this->b = floatToByteAnd(this->b, color.b);
	this->a = floatToByteAnd(this->a, color.a);
	return *this;
}
Color& Color::operator|=(const Color& color)
{
	this->r = floatToByteOr(this->r, color.r);
	this->g = floatToByteOr(this->g, color.g);
	this->b = floatToByteOr(this->b, color.b);
	this->a = floatToByteOr(this->a, color.a);
	return *this;
}
Color& Color::operator^=(const Color& color)
{
	this->r = floatToByteNor(this->r, color.r);
	this->g = floatToByteNor(this->g, color.g);
	this->b = floatToByteNor(this->b, color.b);
	this->a = floatToByteNor(this->a, color.a);
	return *this;
}
Color& Color::operator&=(float num)
{
	this->r = floatToByteAnd(this->r, num);
	this->g = floatToByteAnd(this->g, num);
	this->b = floatToByteAnd(this->b, num);
	this->a = floatToByteAnd(this->a, num);
	return *this;
}
Color& Color::operator|=(float num)
{
	this->r = floatToByteOr(this->r, num);
	this->g = floatToByteOr(this->g, num);
	this->b = floatToByteOr(this->b, num);
	this->a = floatToByteOr(this->a, num);
	return *this;
}
Color& Color::operator^=(float num)
{
	this->r = floatToByteNor(this->r, num);
	this->g = floatToByteNor(this->g, num);
	this->b = floatToByteNor(this->b, num);
	this->a = floatToByteNor(this->a, num);
	return *this;
}

Color Color::operator&(const Color& color) const
{
	return Color(
		floatToByteAnd(this->r, color.r),
		floatToByteAnd(this->g, color.g),
		floatToByteAnd(this->b, color.b),
		floatToByteAnd(this->a, color.a));
}
Color Color::operator|(const Color& color) const
{
	return Color(
		floatToByteOr(this->r, color.r),
		floatToByteOr(this->g, color.g),
		floatToByteOr(this->b, color.b),
		floatToByteOr(this->a, color.a));
}
Color Color::operator^(const Color& color) const
{
	return Color(
		floatToByteNor(this->r, color.r),
		floatToByteNor(this->g, color.g),
		floatToByteNor(this->b, color.b),
		floatToByteNor(this->a, color.a));
}
Color Color::operator~() const
{
	return Color(
		floatToByteBack(this->r),
		floatToByteBack(this->g),
		floatToByteBack(this->b),
		floatToByteBack(this->a));
}
Color Color::operator&(float num) const
{
	return Color(*this & num);
}
Color Color::operator|(float num) const
{
	return Color(*this | num);
}
Color Color::operator^(float num) const
{
	return Color(*this ^ num);
}
bool Color::operator==(const Color& color) const { return equals(color); }
bool Color::operator!=(const Color& color) const { return !equals(color); }
Color Color::ColorRandom(float opacity)
{
	return Color(
		(float)(rand() % 1001 / 1000.0f),
		(float)(rand() % 1001 / 1000.0f),
		(float)(rand() % 1001 / 1000.0f),
		opacity);
}
bool Color::equals(const Color& color) const
{
	if (this->r != color.r) { return false; }
	if (this->g != color.g) { return false; }
	if (this->b != color.b) { return false; }
	if (this->a != color.a) { return false; }
	return true;
}
void Color::setValue(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}