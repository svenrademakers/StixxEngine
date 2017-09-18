#include "FileSystem.hpp"
#include <fstream>

namespace sx
{
	std::vector<uint32_t> FileSystemStd::LoadFile(const std::string& fileName)
	{
		std::ifstream file(fileName, std::ios::ate | std::ios::binary);
		file.seekg(0, std::ios::end);
		std::vector<uint32_t> data(file.tellg());
		file.seekg(0, std::ios::beg);

		data.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		return data;
	}
}
