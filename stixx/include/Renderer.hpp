#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include "Mesh.hpp"

namespace sx
{
	class Renderer
	{
	public:
		virtual ~Renderer(){};
		virtual void LoadScene(const std::vector<sx::Vertex>& vertices, const std::vector<uint32_t>& indices) =0;
		virtual void Draw()  = 0;
	};
}

#endif /* RENDERER_HPP */
