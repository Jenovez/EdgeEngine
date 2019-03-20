// cpp文件

#include "FileUtils.h"

USING_NS_EDGE;

std::string FileUtils::readStringFromFile(const std::string& filename)
{
	std::ifstream in(filename.c_str(), std::ios::in | std::ios::ate);
	if (!in.is_open()) { return ""; }
	std::string result;
	do
	{
		std::size_t size = (std::size_t)in.tellg();
		if (size == 0) { break; }
		in.seekg(std::ios::beg);
		char* buffer = new(std::nothrow) char[size];
		assert(buffer && "FileUtils");
		if (!buffer) { break; }
		memset(buffer, 0, size);
		in.read(buffer, size);
		result = buffer;
		delete[] buffer;
	} while (0);
	in.close();
	return result;
}

bool FileUtils::writeStringToFile(const std::string& filename, const std::string& str)
{
	std::ofstream out(filename.c_str(), std::ios::out);
	if (!out.is_open()) { return false; }
	out << str.c_str();
	out.close();
	return true;
}

Data FileUtils::readBinaryFromFile(const std::string& filename, bool reverse)
{
	Data result;
	std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if (!in.is_open()) { return result; }
	do
	{
		std::size_t size = (std::size_t)in.tellg();
		if (size == 0) { break; }
		in.seekg(0, std::ios::beg);
		char* buffer = new(std::nothrow) char[size];
		assert(buffer && "FileUtils");
		if (!buffer) { break; }
		memset(buffer, 0, size);
		in.read(buffer, size);
		result.setValue((Byte*)buffer, size);
		if (reverse)
		{
			for (ULong i = 0; i < size; ++i)
			{
				result[i] = buffer[size - i - 1];
			}
		}
		delete[] buffer;
	} while (0);
	in.close();
	return result;
}

bool FileUtils::writeBinaryToFile(const std::string& filename, const char* data, std::size_t size, bool reverse)
{
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::binary);
	if (!out.is_open()) { return false; }
	do
	{
		if (reverse)
		{
			char* buffer = new(std::nothrow) char[size];
			assert(buffer && "FileUtils");
			if (!buffer) { break; }
			for (ULong i = 0; i < size; ++i)
			{
				buffer[i] = data[size - i - 1];
			}
			out.write(buffer, size);
			delete[] buffer;
		}
		else
		{
			out.write(data, size);
		}
	} while (0);
	out.close();
	return true;
}

std::size_t FileUtils::getFileSize(const std::string& filename)
{
	std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if (!in.is_open()) { return 0; }
	std::size_t size = (std::size_t)in.tellg();
	in.close();
	return size;
}

bool FileUtils::isFileExist(const std::string& filename)
{
	std::ifstream in(filename.c_str(), std::ios::in);
	if (!in.is_open()) { return false; }
	in.close();
	return true;
}

