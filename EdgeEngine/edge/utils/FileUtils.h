/********************************************
名称:
说明:
1.
********************************************/

#ifndef __FILE_UTILS_H_H__
#define __FILE_UTILS_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>

NS_EDGE_BEGIN

class EDGE_DLL FileUtils final
{
public:
	static std::string readStringFromFile(const std::string& filename);
	static bool writeStringToFile(const std::string& filename, const std::string& str);

	static Data readBinaryFromFile(const std::string& filename, bool reverse = false);
	static bool writeBinaryToFile(const std::string& filename, const char* data, std::size_t size, bool reverse = false);

	static std::size_t getFileSize(const std::string& filename);
	static bool isFileExist(const std::string& filename);
};

NS_EDGE_END

#endif // __FILE_UTILS_H_H__