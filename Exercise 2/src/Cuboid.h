#ifndef Example2_Cuboid_h
#define Example2_Cuboid_h

#include "Shape.h"
#include <glm/vec3.hpp> // glm::vec3

namespace cgCourse
{
	class Cuboid : public Shape
	{
	public:
		Cuboid();
	protected:
		float shapeFunction(float x);
	};
}

#endif
