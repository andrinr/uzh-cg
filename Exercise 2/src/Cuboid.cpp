#include "Cuboid.h"
#include <iostream>

// this define and include will enable M_PI from math.h.
#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse
{
	Cuboid::Cuboid() : Shape()
	{
		/* TODO: add you code here
                */

		int nSegments = 200;
		float radius = 0.8f;
		float shapeSize = 4.f;

		glm::vec3 perpendicularZ = glm::vec3(0., 0., 1.) * radius;

		for (int i = 0; i < nSegments - 1; i++)
		{
			float x = shapeSize / nSegments * i - shapeSize / 2.f;
			float x_1 = shapeSize / nSegments * (i + 1) - shapeSize / 2.f;
			float x_2 = shapeSize / nSegments * (i + 2) - shapeSize / 2.f;
			float y = shapeFunction(x);
			float y_1 = shapeFunction(x_1);
			float y_2 = shapeFunction(x_2);

			glm::vec3 linePointA = glm::vec3(x, y, 0);
			glm::vec3 linePointB = glm::vec3(x_1, y_1, 0);
			glm::vec3 perpendicularAXY = glm::normalize(glm::vec3(y_1 - y, -(x_1 - x), 0)) * radius;
			glm::vec3 perpendicularBXY = glm::normalize(glm::vec3(y_2 - y_1, -(x_2 - x_1), 0)) * radius;

			// Bottom cap
			if (i == 0)
			{
				glm::vec3 capVertices[4] = {
					glm::vec3(linePointA) + perpendicularAXY, // index 0
					glm::vec3(linePointA) + perpendicularZ,
					glm::vec3(linePointA) - perpendicularAXY, // index 0
					glm::vec3(linePointA) - perpendicularZ,
				};

				glm::vec3 capColors[4] = {
					{0.0f, 0.8f, 0.8f},
					{0.0f, 0.8f, 0.8f},
					{0.0f, 0.8f, 0.8f},
					{0.0f, 0.8f, 0.8f}};

				glm::vec3 capFaces[2] = {
					{0, 1, 2},
					{0, 2, 3}};

				for (int j = 0; j < 4; j++)
				{
					this->positions.push_back(capVertices[j]);
					this->colors.push_back(capColors[j]);
				};

				for (int j = 0; j < 2; j++)
				{
					this->faces.push_back(capFaces[j]);
				};
			};

			glm::vec3 vertices[16] = {
				glm::vec3(linePointA) + perpendicularAXY, // index 0
				glm::vec3(linePointA) + perpendicularZ,
				glm::vec3(linePointB) + perpendicularBXY,
				glm::vec3(linePointB) + perpendicularZ,

				glm::vec3(linePointA) + perpendicularZ,
				glm::vec3(linePointA) - perpendicularAXY,
				glm::vec3(linePointB) + perpendicularZ,
				glm::vec3(linePointB) - perpendicularBXY,

				glm::vec3(linePointA) - perpendicularAXY,
				glm::vec3(linePointA) - perpendicularZ,
				glm::vec3(linePointB) - perpendicularBXY,
				glm::vec3(linePointB) - perpendicularZ,

				glm::vec3(linePointA) - perpendicularZ,
				glm::vec3(linePointA) + perpendicularAXY,
				glm::vec3(linePointB) - perpendicularZ,
				glm::vec3(linePointB) + perpendicularBXY,
			};

			glm::vec3 colors[16] = {
				{0.8f, 0.8f, 0.0f},
				{0.8f, 0.8f, 0.0f},
				{0.8f, 0.8f, 0.0f},
				{0.8f, 0.8f, 0.0f},

				{0.8f, 0.0f, 0.0f},
				{0.8f, 0.0f, 0.0f},
				{0.8f, 0.0f, 0.0f},
				{0.8f, 0.0f, 0.0f},

				{0.0f, 0.8f, 0.0f},
				{0.0f, 0.8f, 0.0f},
				{0.0f, 0.8f, 0.0f},
				{0.0f, 0.8f, 0.0f},

				{0.0f, 0.0f, 0.8f},
				{0.0f, 0.0f, 0.8f},
				{0.0f, 0.0f, 0.8f},
				{0.0f, 0.0f, 0.8f}
			};

			float indexOffset = i * 16.f + 4.f;

			glm::uvec3 faces[8] = {
				{0 + indexOffset, 2 + indexOffset, 1 + indexOffset},
				{1 + indexOffset, 2 + indexOffset, 3 + indexOffset},
				{4 + indexOffset, 6 + indexOffset, 5 + indexOffset},
				{5 + indexOffset, 6 + indexOffset, 7 + indexOffset},
				{8 + indexOffset, 10 + indexOffset, 9 + indexOffset},
				{9 + indexOffset, 10 + indexOffset, 11 + indexOffset},
				{12 + indexOffset, 14 + indexOffset, 13 + indexOffset},
				{13 + indexOffset, 14 + indexOffset, 15 + indexOffset}
			};

			for (int j = 0; j < 16; j++)
			{
				this->positions.push_back(vertices[j]);
				this->colors.push_back(colors[j]);
			};

			for (int j = 0; j < 8; j++)
			{
				this->faces.push_back(faces[j]);
			};

			// Top cap
			if (i == nSegments - 2)
			{
				glm::vec3 capVertices[4] = {
					glm::vec3(linePointB) + perpendicularBXY, // index 0
					glm::vec3(linePointB) + perpendicularZ,
					glm::vec3(linePointB) - perpendicularBXY, // index 0
					glm::vec3(linePointB) - perpendicularZ,
				};

				glm::vec3 capColors[4] = {
					{0.8f, 0.f, 0.8f},
					{0.8f, 0.f, 0.8f},
					{0.8f, 0.f, 0.8f},
					{0.8f, 0.f, 0.8f}};

				glm::vec3 capFaces[2] = {
					{indexOffset + 16 + 2, indexOffset + 16 + 1, indexOffset + 16 + 0},
					{indexOffset + 16 + 0, indexOffset + 16 + 3, indexOffset + 16 + 2}
				};

				for (int j = 0; j < 4; j++)
				{
					this->positions.push_back(capVertices[j]);
					this->colors.push_back(capColors[j]);
				};

				for (int j = 0; j < 2; j++)
				{
					this->faces.push_back(capFaces[j]);
				};
			};
		};
		// for the moment we don't add normals here that is why we will not set the normals or face normals.
	};

	float Cuboid::shapeFunction(float x)
	{
		return x * x * x - 1;
	};
}
