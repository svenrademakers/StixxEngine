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
		virtual std::vector<uint32_t> LoadFile(std::string fileName) const = 0;
	};

	class FileSystemStd
		: public  FileSystem
	{
	public:
		virtual std::vector<uint32_t> LoadFile(std::string fileName) const override;
	};
}

#endif /* FILESYSTEM_HPP */
