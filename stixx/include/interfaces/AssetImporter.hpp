#ifndef ASSET_IMPORTER_HPP
#define ASSET_IMPORTER_HPP

#include <memory>
#include "renderer/Mesh.hpp"

namespace sx
{
	class AssetImporter
	{
	public:
		virtual ~AssetImporter() {};
		virtual void Load(const char * path) = 0;
		virtual bool Next(Mesh& mesh) = 0;
	};

	class AssetImporterFactory
	{
	public:
		virtual std::unique_ptr<AssetImporter> Importer() = 0;
	};

	template<class T>
	class AssetImporterFactoryImpl
		: AssetImporterFactory
	{
	public:
		virtual std::unique_ptr<AssetImporter> Importer()
		{
			return std::make_unique<T>();
		}
	};
}

#endif
