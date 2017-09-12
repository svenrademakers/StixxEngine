/*
 * MeshLoader.hpp
 *
 *  Created on: 10 Sep 2017
 *      Author: svenrademakers
 */

#ifndef MESHLOADER_HPP_
#define MESHLOADER_HPP_

#include "Mesh.h"

namespace sxgraphics
{
	class MeshLoader
	{
	public:
		virtual ~MeshLoader() {};
		virtual bool Next(std::vector<sxgraphics::Vertex>&, std::vector<unsigned int>&, std::vector<sxgraphics::Texture>&) = 0;
	};
}

#endif /* ASSETLOADER_HPP_ */
