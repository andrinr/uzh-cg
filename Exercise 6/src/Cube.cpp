#include "Cube.h"

namespace cgCourse
{
	Cube::Cube() : Shape()
	{
		// set geometry with respect to local origin
		this->positions = {
			{ -1.0f, -1.0f, -1.0f },   // index 0
			{ -1.0f, -1.0f, 1.0f },
			{ -1.0f, 1.0f, 1.0f },
			{ -1.0f, 1.0f, -1.0f },

			{ 1.0f, 1.0f, 1.0f },      // index 4
			{ 1.0f, -1.0f, 1.0f },
			{ 1.0f, -1.0f, -1.0f },
			{ 1.0f, 1.0f, -1.0f },

			{ -1.0f, -1.0f, -1.0f },   // index 8
			{ 1.0f, -1.0f, -1.0f },
			{ 1.0f, -1.0f, 1.0f },
			{ -1.0f, -1.0f, 1.0f },

			{ 1.0f, 1.0f, 1.0f },      // index 12
			{ 1.0f, 1.0f, -1.0f },
			{ -1.0f, 1.0f, -1.0f },
			{ -1.0f, 1.0f, 1.0f },

			{ -1.0f, -1.0f, -1.0f },   // index 16
			{ -1.0f, 1.0f, -1.0f },
			{ 1.0f, 1.0f, -1.0f },
			{ 1.0f, -1.0f, -1.0f },

			{ 1.0f, 1.0f, 1.0f },      // index 20
			{ -1.0f, 1.0f, 1.0f },
			{ -1.0f, -1.0f, 1.0f },
			{ 1.0f, -1.0f, 1.0f }
		};

		this->colors = {
			{ 0.8f, 0.8f, 0.0f },
			{ 0.8f, 0.8f, 0.0f },
			{ 0.8f, 0.8f, 0.0f },
			{ 0.8f, 0.8f, 0.0f },

			{ 0.8f, 0.0f, 0.0f },
			{ 0.8f, 0.0f, 0.0f },
			{ 0.8f, 0.0f, 0.0f },
			{ 0.8f, 0.0f, 0.0f },

			{ 0.0f, 0.8f, 0.0f },
			{ 0.0f, 0.8f, 0.0f },
			{ 0.0f, 0.8f, 0.0f },
			{ 0.0f, 0.8f, 0.0f },

			{ 0.0f, 0.0f, 0.8f },
			{ 0.0f, 0.0f, 0.8f },
			{ 0.0f, 0.0f, 0.8f },
			{ 0.0f, 0.0f, 0.8f },

			{ 0.0f, 0.8f, 0.8f },
			{ 0.0f, 0.8f, 0.8f },
			{ 0.0f, 0.8f, 0.8f },
			{ 0.0f, 0.8f, 0.8f },

			{ 0.8f, 0.0f, 0.8f },
			{ 0.8f, 0.0f, 0.8f },
			{ 0.8f, 0.0f, 0.8f },
			{ 0.8f, 0.0f, 0.8f }
		};

		this->normals = {
			{ -1.0f, 0.0f, 0.0f },
			{ -1.0f, 0.0f, 0.0f },
			{ -1.0f, 0.0f, 0.0f },
			{ -1.0f, 0.0f, 0.0f },

			{ 1.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 0.0f },

			{ 0.0f, -1.0f, 0.0f },
			{ 0.0f, -1.0f, 0.0f },
			{ 0.0f, -1.0f, 0.0f },
			{ 0.0f, -1.0f, 0.0f },

			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },

			{ 0.0f, 0.0f, -1.0f },
			{ 0.0f, 0.0f, -1.0f },
			{ 0.0f, 0.0f, -1.0f },
			{ 0.0f, 0.0f, -1.0f },

			{ 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f }
		};

		this->texCoords = {
			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },

			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },

			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },

			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },

			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },

			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f }
		};

		this->faces = {
			{ 0, 1, 2 }, { 2, 3, 0 },
			{ 4, 5, 6 }, { 6, 7, 4 },
			{ 8, 9, 10 }, { 10, 11, 8 },
			{ 12, 13, 14 }, { 14, 15, 12 },
			{ 16, 17, 18 }, { 18, 19, 16 },
			{ 20, 21, 22 }, { 22, 23, 20 }
		};

		this->faceNormals = {
			{ -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },
			{ 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, -1.0f },
			{ 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }
		};
        
        /* TODO: add the tangent vectors for the cube here to
         *       to the tangent array.
         *
         */

		for (int i = 0; i < this->faces.size(); i++){
			int i1 = this->faces[i].x;
			int i2 = this->faces[i].y;
			int i3 = this->faces[i].z;

			glm::vec3 v1 = this->positions[i1];
			glm::vec3 v2 = this->positions[i2];
			glm::vec3 v3 = this->positions[i3];

			glm::vec2 t1 = this->texCoords[i1];
			glm::vec2 t2 = this->texCoords[i2];
			glm::vec2 t3 = this->texCoords[i3];

			glm::vec3 e1 = v2 - v1;
			glm::vec3 e2 = v3 - v1;

			glm::vec2 duv1 = t2 - t1;
			glm::vec2 duv2 = t3 - t1;

			float f = 1.0f / (duv1.x * duv2.y - duv2.x * duv1.y);

			glm::vec3 tangent = {
				f * (duv2.y * e1.x - duv1.y * e2.x),
				f * (duv2.y * e1.y - duv1.y * e2.y),
				f * (duv2.y * e1.z - duv1.y * e2.z)
			};

			glm::vec3 bitangent = {
				f * (-duv2.x * e1.x - duv1.x * e2.x),
				f * (-duv2.x * e1.y - duv1.x * e2.y),
				f * (-duv2.x * e1.z - duv1.x * e2.z)
			};

			this->tangents.push_back(
				tangent
			);

			this->tangents.push_back(
				bitangent
			);
		};
    


        // End TODO
	}
}
