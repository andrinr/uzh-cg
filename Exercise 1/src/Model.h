#ifndef MODELS_HPP_INCLUDED
#define MODELS_HPP_INCLUDED

#include "GLIncludes.h"

namespace cgCourse
{

	class Model
	{
	public:
		static const GLuint InvalidAttribLoc;

		Model();
		virtual ~Model();

		virtual bool createVertexArray(GLuint posAttribLoc,
			GLuint colAttribLoc,
			GLuint normAttribLoc) = 0;

		virtual GLuint getVertexArrayId() const = 0;
		virtual GLenum getDrawElemType() const = 0;
		virtual GLsizei getDrawElemCount() const = 0;
	};

	class Cube : public Model
	{
	public:
		Cube();
		virtual ~Cube() override;

		virtual bool createVertexArray(GLuint posAttribLoc,
			GLuint colAttribLoc,
			GLuint normAttribLoc) override;

		virtual GLuint getVertexArrayId() const override;
		virtual GLenum getDrawElemType() const override;
		virtual GLsizei getDrawElemCount() const override;

	private:
		GLuint modelVAO_;
		GLuint posBO_;
		GLuint colBO_;
		GLuint normBO_;
		GLuint idxBO_;
	};

}

#endif // MODELS_HPP_INCLUDED
