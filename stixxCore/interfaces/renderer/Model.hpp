#ifndef MODEL_HPP
#define MODEL_HPP

#include <glm/glm.hpp>

namespace sx
{
	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	class Model
	{
	public:
		virtual ~Model() {};
		virtual void UpdateUbo(UniformBufferObject& ubo) = 0;
	};
}
#endif
