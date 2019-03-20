/********************************************
名称:
说明:
1.
********************************************/

#ifndef __DATA_H_H__
#define __DATA_H_H__

#include <base/CommonConfig.h>

NS_EDGE_BEGIN

class EDGE_DLL Data final
{
public:
	Byte* bin;
	ULong size;

public: // constant
	static const Data ZERO;

public: // construction functions
	Data();
	Data(const Data& data);
	Data(const Byte* binary, ULong length);
	~Data();

public: // operator functions
	Data& operator=(const Data& data);

	Byte& operator[](ULong index) const;

	bool operator==(const Data& data) const;
	bool operator!=(const Data& data) const;

public: // common use functions
	void setValue(const Byte* binary, ULong length);
	bool equals(const Data& data) const;
	Byte& at(ULong index) const;

private: // unable dynamic alloc
	void* operator new(size_t);
	void operator delete(void*);
};

NS_EDGE_END

#endif // __DATA_H_H__