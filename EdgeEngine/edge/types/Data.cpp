// cpp文件

#include "Data.h"

USING_NS_EDGE;

const Data Data::ZERO;

Data::Data()
: bin(0)
, size(0)
{}

Data::Data(const Data& data)
: bin(0)
, size(0)
{
	setValue(data.bin, data.size);
}

Data::Data(const Byte* bin, ULong length)
: bin(0)
, size(0)
{
	setValue(bin, length);
}

Data::~Data()
{
	if (bin)
	{
		delete[] bin;
	}
}

Data& Data::operator=(const Data& data)
{
	setValue(data.bin, data.size);
	return *this;
}

Byte& Data::operator[](ULong index) const
{
	return at(index);
}


bool Data::operator==(const Data& data) const
{
	return equals(data);
}

bool Data::operator!=(const Data& data) const
{
	return !equals(data);
}

void Data::setValue(const Byte* b, ULong l)
{
	if (bin)
	{
		delete[] bin;
		bin = 0;
	}

	bin = new Byte[l];
	memset(bin, 0, l);
	for (ULong i = 0; i < l; ++i)
	{
		bin[i] = b[i];
	}
	size = l;
}

bool Data::equals(const Data& data) const
{
	if (size != data.size) { return false; }
	for (ULong i = 0; i < data.size; ++i)
	{
		if (bin[i] != data.bin[i]) { return false; }
	}
	return true;
}

Byte& Data::at(ULong index) const
{
	assert(index >= 0 && index < size);
	return bin[index];
}