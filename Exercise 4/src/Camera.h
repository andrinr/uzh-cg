#ifndef Example_Camera_h
#define Example_Camera_h

#include "GLIncludes.h"
#include <glm/gtc/matrix_transform.hpp>

namespace cgCourse
{
	class Camera
	{
	public:
		Camera();

		void create(
			glm::uvec2 _extent,
			glm::vec3 _pos,
			glm::vec3 _origin,
			glm::vec3 _up);
        
		void setViewport(glm::uvec2 _extent);

		glm::vec3 getPosition() const;
		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;
		glm::mat4 getViewProjectionMatrix() const;

    private:
		void computeViewProjectionMatrix();
		void computeProjectionMatrix(glm::uvec2 _extent);
		void computeViewMatrix(glm::vec3 _pos, glm::vec3 _origin, glm::vec3 _up);

		glm::vec3 position;
		glm::vec3 origin;
		glm::vec3 up;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 viewProjectionMatrix;
	};
}

#endif
