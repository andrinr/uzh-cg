#ifndef Example_Shape_h
#define Example_Shape_h

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
		GLsizei getDrawElemCount() const;
        virtual void draw() const;
        
		std::vector< glm::vec3 >& getPositions();
		std::vector< glm::vec3 >& getNormals();
		std::vector< glm::uvec3 >& getFaces();
		std::vector< glm::vec3 >& getFaceNormals();

		glm::mat4 getModelMatrix() const;
		glm::vec3 getPosition();
		
        void setPosition(glm::vec3);
        void setRotation(float _angle, glm::vec3 _rot);
        void setScaling(glm::vec3 _scale);
		void calculateModelMatrix();
        
	protected:
        virtual void initIndexBuffer();
        
		std::vector< glm::vec3 > positions;
		std::vector< glm::vec3 > colors;
		std::vector< glm::vec3 > normals;
		std::vector< glm::uvec3 > faces;
		std::vector< glm::vec3 > faceNormals;

		glm::vec3 objectPosition;

        glm::mat4 rotationMatrix;
        glm::mat4 translationMatrix;
        glm::mat4 scalingMatrix;
        glm::mat4 modelMatrix;
		
		GLuint vaoID;
		GLuint posBufferID;
		GLuint colorBufferID;
		GLuint normalBufferID;
		GLuint indexBufferID;
	};
}

#endif

