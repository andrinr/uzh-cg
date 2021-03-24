#ifndef Example2_GeometryModels_h
#define Example2_GeometryModels_h

#include "GLIncludes.h"
#include <vector>
#include <glm/mat4x4.hpp>

namespace cgCourse
{
	class Shape
	{
	public:
		Shape();
		virtual ~Shape();

		bool createVertexArray(GLuint posAttribLoc,
			GLuint colAttribLoc,
			GLuint normAttribLoc);

		GLuint getVertexArrayId() const;
		GLenum getDrawElemType() const;
		GLsizei getDrawElemCount() const;

		std::vector< glm::vec3 >& getPositions();
		std::vector< glm::vec3 >& getNormals();
		std::vector< glm::uvec3 >& getFaces();
		std::vector< glm::vec3 >& getFaceNormals();

		glm::mat4 getModelMatrix() const;

		void setShapePosition(glm::vec3);

	protected:
		std::vector< glm::vec3 > positions;
		std::vector< glm::vec3 > colors;
		std::vector< glm::vec3 > normals;
		std::vector< glm::uvec3 > faces;
		std::vector< glm::vec3 > faceNormals;

		// Model matrix of this object
		glm::mat4 modelMatrix;;

	private:
		GLuint vaoID;
		GLuint posBufferID;
		GLuint colorBufferID;
		GLuint normalBufferID;
		GLuint indexBufferID;
	};
}

#endif

