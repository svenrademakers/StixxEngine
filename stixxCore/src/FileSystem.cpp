#include <fstream>
#include "FileSystem.hpp"

namespace sx
{
	CannotOpenFileException::CannotOpenFileException(const std::string path)
		: path(path)
	{}

	void FileSystemImpl::ReadBinary(const std::string fileName, const std::function<void(std::istream&)> streamAvailable) const
	{
		std::ifstream input(fileName, std::ios::binary);

		if (!input)
			throw CannotOpenFileException(fileName);

		streamAvailable(input);
	}

	void FileSystemImpl::WriteBinary(const std::string fileName, const std::function<void(std::ostream&)> streamAvailable) const
	{
		std::ofstream output(fileName, std::ios::binary);

		if (!output)
			throw CannotOpenFileException(fileName);

		streamAvailable(output);
	}
}