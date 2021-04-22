#include "Camera.h"
#include <iostream>

// to get M_PI from math libary enable defines
#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse
{
	Camera::Camera()
	{
		
	}

	void Camera::create(glm::uvec2 _extent, glm::vec3 _pos, glm::vec3 _origin, glm::vec3 _up)
	{
		this->computeViewMatrix(_pos, _origin, _up);
		this->setViewport(_extent);
	}
    
	void Camera::setViewport(glm::uvec2 _extent)
	{
		glViewport(0, 0, int(_extent.x), int(_extent.y));
		this->computeProjectionMatrix(_extent);
		this->computeViewProjectionMatrix();
	}

	void Camera::computeViewProjectionMatrix()
	{
		this->viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void Camera::computeViewMatrix(glm::vec3 _pos, glm::vec3 _origin, glm::vec3 _up)
	{
		this->position = _pos;
		this->origin = _origin;
		this->up = _up;
		this->viewMatrix = glm::lookAt(_pos,_origin,_up);
	}

	void Camera::computeProjectionMatrix(glm::uvec2 _extent)
	{
		// Projection matrix
		float fieldOfView = 45.0f;
		float nearPlane = 0.1;
		float farPlane = 50.0;
		float aspect = float(_extent.x) / float(_extent.y);

		this->projectionMatrix = glm::perspective(fieldOfView, aspect,
			nearPlane, farPlane);
	}
    
	glm::vec3 Camera::getPosition() const
	{
		return this->position;
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return this->viewMatrix;
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		return this->projectionMatrix;
	}

	glm::mat4 Camera::getViewProjectionMatrix() const
	{
		return this->viewProjectionMatrix;
	}
}
