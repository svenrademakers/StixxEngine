#include "FileSystem.hpp"
#include <fstream>
#include <stdexcept>
#include <string>

namespace sx
{
	std::vector<uint32_t> FileSystemStd::LoadFile(std::string fileName) const
	{
		std::ifstream file(fileName, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<uint32_t> buffer(fileSize);

		file.seekg(0);
		file.read(reinterpret_cast<char *>(buffer.data()), fileSize);

		file.close();

		return buffer;
	}
}
