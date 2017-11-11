/*
 * MeshLoader.hpp
 *
 *  Created on: 10 Sep 2017
 *      Author: svenrademakers
 */

#ifndef MESHLOADER_HPP_
#define MESHLOADER_HPP_

#include "renderer/Mesh.hpp"

namespace sx
{
	class MeshLoader
	{
	public:
		virtual ~MeshLoader() {};
		virtual bool Next(Mesh& mesh) = 0;
	};
}

#endif /* ASSETLOADER_HPP_ */
