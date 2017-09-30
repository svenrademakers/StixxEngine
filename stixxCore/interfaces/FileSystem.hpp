#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <vector>
#include <string>

namespace sx
{
	class FileSystem
	{
	public:
		virtual ~FileSystem() {};
		virtual std::vector<uint32_t> LoadFile(const char* fileName) = 0;
	};

	class FileSystemStd
		: public  FileSystem
	{
	public:
		virtual std::vector<uint32_t> LoadFile(const char* fileName) override;
	};
}

#endif /* FILESYSTEM_HPP */