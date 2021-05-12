#include "MultiLine.h"
#include <iostream>

// to get M_PI from math libary enable defines
#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse
{
	MultiLine::MultiLine(const std::vector< glm::vec3 >& _vertices,
                         const std::vector< glm::vec3 >& _normals) : Shape()
	{
        // calculate positions for vertex normals
		for (int j = 0; j < _vertices.size(); j++)
		{
            this->positions.push_back(_vertices[j]);
            this->positions.push_back(_vertices[j] + (_normals[j] * 0.25f));
            // line indices add for every line 2 indices from tail to head
            lineIndices.push_back(glm::uvec2((j*2),(j*2)+1));
            
            this->colors.push_back(glm::vec3(1.0,1.0,0.0));
            this->colors.push_back(glm::vec3(1.0,1.0,0.0));
		}
	}
    
    void MultiLine::draw() const
    {
        // bind the Vertex Array Object and draw the lines
        glBindVertexArray(this->getVertexArrayId());
        glDrawElements(GL_LINES, this->lineIndices.size() * 2, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    
    void MultiLine::initIndexBuffer() {
        // Initialize buffer objects with index data
        glGenBuffers(1, &indexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, lineIndices.size() * sizeof(glm::uvec2),
                     lineIndices.data(), GL_STATIC_DRAW);
    }
    
}
