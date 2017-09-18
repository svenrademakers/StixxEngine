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
		virtual std::vector<char> LoadFile(const std::string& fileName) = 0;
	};

	class FileSystemStd
		: public  FileSystem
	{
	public:
		virtual std::vector<char> LoadFile(const std::string& fileName) override;
	};
}

#endif /* FILESYSTEM_HPP */
