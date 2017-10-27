#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <vector>
#include <string>
#include <exception>
#include <istream>
#include <functional>

namespace sx
{
	struct CannotOpenFileException
		: std::exception
	{
		CannotOpenFileException(const std::string path);
		const std::string path;
	};

	class File
	{
	public:
		virtual ~File() = default;
		virtual void Load(std::istream& filestream) = 0;
		virtual void Save(std::ostream& filestream) = 0;
	};

	class FileSystem
	{
	public:
		virtual ~FileSystem() = default;
		virtual void ReadBinary(const std::string fileName, const std::function<void(std::istream&)> streamAvailable) const = 0;
		virtual void WriteBinary(const std::string fileName, const std::function<void(std::ostream&)> streamAvailable) const = 0;
	};

	class FileSystemImpl
		: public FileSystem
	{
	public:
		FileSystemImpl() = default;
		virtual ~FileSystemImpl() = default;

		void ReadBinary(const std::string fileName, const std::function<void(std::istream&)> streamAvailable) const override;
		void WriteBinary(const std::string fileName, const std::function<void(std::ostream&)> streamAvailable) const override;
	};
}

#endif
