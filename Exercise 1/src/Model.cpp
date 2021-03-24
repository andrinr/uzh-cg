#include "Model.h"

namespace cgCourse
{
	// ---- Model ----
	const GLuint Model::InvalidAttribLoc = GLuint(-1);

	Model::Model()
	{ }

	Model::~Model()
	{ }


	// ---- Cube ----
	namespace
	{
		namespace CubeData
		{
			static const float Vertices[] =
			{
				-1.0f, -1.0f, -1.0f,   // index 0
				-1.0f, -1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, -1.0f,

				1.0f, 1.0f, 1.0f,      // index 4
				1.0f, -1.0f, 1.0f,
				1.0f, -1.0f, -1.0f,
				1.0f, 1.0f, -1.0f,

				-1.0f, -1.0f, -1.0f,   // index 8
				1.0f, -1.0f, -1.0f,
				1.0f, -1.0f, 1.0f,
				-1.0f, -1.0f, 1.0f,

				1.0f, 1.0f, 1.0f,      // index 12
				1.0f, 1.0f, -1.0f,
				-1.0f, 1.0f, -1.0f,
				-1.0f, 1.0f, 1.0f,

				-1.0f, -1.0f, -1.0f,   // index 16
				-1.0f, 1.0f, -1.0f,
				1.0f, 1.0f, -1.0f,
				1.0f, -1.0f, -1.0f,

				1.0f, 1.0f, 1.0f,      // index 20
				-1.0f, 1.0f, 1.0f,
				-1.0f, -1.0f, 1.0f,
				1.0f, -1.0f, 1.0f
			};

			static const float Colors[] =
			{
				0.8f, 0.8f, 0.0f,
				0.8f, 0.8f, 0.0f,
				0.8f, 0.8f, 0.0f,
				0.8f, 0.8f, 0.0f,

				0.8f, 0.0f, 0.0f,
				0.8f, 0.0f, 0.0f,
				0.8f, 0.0f, 0.0f,
				0.8f, 0.0f, 0.0f,

				0.0f, 0.8f, 0.0f,
				0.0f, 0.8f, 0.0f,
				0.0f, 0.8f, 0.0f,
				0.0f, 0.8f, 0.0f,

				0.0f, 0.0f, 0.8f,
				0.0f, 0.0f, 0.8f,
				0.0f, 0.0f, 0.8f,
				0.0f, 0.0f, 0.8f,

				0.0f, 0.8f, 0.8f,
				0.0f, 0.8f, 0.8f,
				0.0f, 0.8f, 0.8f,
				0.0f, 0.8f, 0.8f,

				0.8f, 0.0f, 0.8f,
				0.8f, 0.0f, 0.8f,
				0.8f, 0.0f, 0.8f,
				0.8f, 0.0f, 0.8f
			};

			static const float Normals[] =
			{
				-1.0f, 0.0f, 0.0f,
				-1.0f, 0.0f, 0.0f,
				-1.0f, 0.0f, 0.0f,
				-1.0f, 0.0f, 0.0f,

				1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,

				0.0f, -1.0f, 0.0f,
				0.0f, -1.0f, 0.0f,
				0.0f, -1.0f, 0.0f,
				0.0f, -1.0f, 0.0f,

				0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,

				0.0f, 0.0f, -1.0f,
				0.0f, 0.0f, -1.0f,
				0.0f, 0.0f, -1.0f,
				0.0f, 0.0f, -1.0f,

				0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f
			};

			static const GLuint Triangles[] =
			{
				0, 1, 2, 2, 3, 0,
				4, 5, 6, 6, 7, 4,
				8, 9, 10, 10, 11, 8,
				12, 13, 14, 14, 15, 12,
				16, 17, 18, 18, 19, 16,
				20, 21, 22, 22, 23, 20
			};
		} // namespace CubeData
	} // namespace 

	Cube::Cube()
		: modelVAO_(0), posBO_(0), colBO_(0), normBO_(0)
	{ }

	Cube::~Cube()
	{
		if (posBO_ != 0)
		{
			glDeleteBuffers(1, &posBO_);
		}
		if (colBO_ != 0)
		{
			glDeleteBuffers(1, &colBO_);
		}
		if (normBO_ != 0)
		{
			glDeleteBuffers(1, &normBO_);
		}
		if (idxBO_ != 0)
		{
			glDeleteBuffers(1, &idxBO_);
		}
		if (modelVAO_ != 0)
		{
			glDeleteVertexArrays(1, &modelVAO_);
		}
	}

	bool Cube::createVertexArray(GLuint posAttribLoc,
		GLuint colAttribLoc,
		GLuint normAttribLoc)
	{
		// Initialize buffer objects with geometry data
		glGenBuffers(1, &posBO_);
		glBindBuffer(GL_ARRAY_BUFFER, posBO_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeData::Vertices),
			CubeData::Vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &colBO_);
		glBindBuffer(GL_ARRAY_BUFFER, colBO_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeData::Colors),
			CubeData::Colors, GL_STATIC_DRAW);

		glGenBuffers(1, &normBO_);
		glBindBuffer(GL_ARRAY_BUFFER, normBO_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeData::Normals),
			CubeData::Normals, GL_STATIC_DRAW);

		// Initialize buffer objects with index data
		glGenBuffers(1, &idxBO_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBO_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeData::Triangles),
			CubeData::Triangles, GL_STATIC_DRAW);

		// initialize cube's vertex array object
		glGenVertexArrays(1, &modelVAO_);
		glBindVertexArray(modelVAO_);

		if (posAttribLoc != Model::InvalidAttribLoc)
		{
			glBindBuffer(GL_ARRAY_BUFFER, posBO_);
			glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(posAttribLoc);
		}

		if (colAttribLoc != Model::InvalidAttribLoc)
		{
			glBindBuffer(GL_ARRAY_BUFFER, colBO_);
			glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(colAttribLoc);
		}

		if (normAttribLoc != Model::InvalidAttribLoc)
		{
			glBindBuffer(GL_ARRAY_BUFFER, normBO_);
			glVertexAttribPointer(normAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(normAttribLoc);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBO_);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return true;
	}

	GLuint Cube::getVertexArrayId() const
	{
		return modelVAO_;
	}

	GLenum Cube::getDrawElemType() const
	{
		return GL_TRIANGLES;
	}

	GLsizei Cube::getDrawElemCount() const
	{
		return sizeof(CubeData::Triangles) / sizeof(GLuint);
	}

}
