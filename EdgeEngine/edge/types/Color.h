#ifndef __COLOR_H_H__
#define __COLOR_H_H__

#include <base/CommonConfig.h>

NS_EDGE_BEGIN

// 表示ARGB的32位颜色
class EDGE_DLL Color final
{
public: // create function
	static Color ColorRandom(float opacity);

public: // variable
	float r;
	float g;
	float b;
	float a;

public: // constant
	static const Color ZERO;
	static const Color WHITE;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;

public: // construction functions
	Color();
	Color(float r, float g, float b, float a);
	Color(const Color& color);

public: // operator functions
	Color& operator&=(const Color& color);
	Color& operator|=(const Color& color);
	Color& operator^=(const Color& color);
	Color& operator&=(float num);
	Color& operator|=(float num);
	Color& operator^=(float num);

	Color operator&(const Color& color) const;
	Color operator|(const Color& color) const;
	Color operator^(const Color& color) const;
	Color operator&(float num) const;
	Color operator|(float num) const;
	Color operator^(float num) const;
	Color operator~() const;

	bool operator==(const Color& color) const;
	bool operator!=(const Color& color) const;

public: // common use functions
	bool equals(const Color& color) const;
	void setValue(float r, float g, float b, float a);

private: // unable dynamic alloc
	void* operator new(size_t);
	void operator delete(void*);
};

NS_EDGE_END

#endif // __COLOR_H_H__