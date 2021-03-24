#include "Shape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cgCourse
{
	Shape::Shape()
		: vaoID(0), posBufferID(0), colorBufferID(0), normalBufferID(0), indexBufferID(0),
		positions(0), colors(0), normals(0), faces(0), faceNormals(0)
	{
		// Model matrix : an identity matrix (model will be at the origin)
		this->modelMatrix = glm::mat4();
	}

	Shape::~Shape()
	{
		if (this->posBufferID != 0)
		{
			glDeleteBuffers(1, &this->posBufferID);
		}
		if (this->colorBufferID != 0)
		{
			glDeleteBuffers(1, &this->colorBufferID);
		}
		if (this->normalBufferID != 0)
		{
			glDeleteBuffers(1, &this->normalBufferID);
		}
		if (this->indexBufferID != 0)
		{
			glDeleteBuffers(1, &this->indexBufferID);
		}
		if (this->vaoID != 0)
		{
			glDeleteVertexArrays(1, &this->vaoID);
		}
	}

	bool Shape::createVertexArray(GLuint posAttribLoc,
		GLuint colAttribLoc,
		GLuint normAttribLoc)
	{
		// check if all buffer locations are somehow defined
		if ((posAttribLoc == GLuint(-1)) ||
			(colAttribLoc == GLuint(-1)) ||
			(normAttribLoc == GLuint(-1)))
		{
			return false;
		}

		// Initialize Vertex Array Object
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

		// Initialize buffer objects with geometry data
		// for positions
		glGenBuffers(1, &posBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, posBufferID);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3),
				positions.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(posAttribLoc);

		// for colors
		glGenBuffers(1, &colorBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3),
				colors.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colAttribLoc);

		// for normals
		glGenBuffers(1, &normalBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),
				normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(normAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(normAttribLoc);

		// Initialize buffer objects with index data
		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(glm::uvec3),
			faces.data(), GL_STATIC_DRAW);

		// Reset state
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return true;
	}

	std::vector< glm::vec3 >& Shape::getPositions()
	{
		return this->positions;
	}

	std::vector< glm::vec3 >& Shape::getNormals()
	{
		return this->normals;
	}

	std::vector< glm::uvec3 >& Shape::getFaces()
	{
		return this->faces;
	}

	std::vector< glm::vec3 >& Shape::getFaceNormals()
	{
		return this->faceNormals;
	}

	void Shape::setShapePosition(glm::vec3 _pos)
	{
		this->modelMatrix = glm::translate(this->modelMatrix, _pos);
	}

	glm::mat4 Shape::getModelMatrix() const
	{
		return this->modelMatrix;
	}

	GLuint Shape::getVertexArrayId() const
	{
		return this->vaoID;
	}

	GLenum Shape::getDrawElemType() const
	{
		return GL_TRIANGLES;
	}

	GLsizei Shape::getDrawElemCount() const
	{
		return 3 * this->faces.size();
	}

}
