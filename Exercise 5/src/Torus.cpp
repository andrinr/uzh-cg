#include "Torus.h"
#include <iostream>

// to get M_PI from math libary enable defines
#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse
{
    
    // a simple 2D circle
    class Circle
    {
    public:
        Circle(float _radius, int _segments){
            this->radius = _radius;
            this->segments = _segments;
            // generated equally distributed segments on this circle
            for (int j = 0; j < this->segments; j++)
            {
                float angle = (float)j * (360.0 / this->segments);
                float radians = Circle::toRadians(angle);
                vertices.push_back(glm::vec2(this->radius * std::sin(radians), this->radius * std::cos(radians)));
            }
        }

        const std::vector<glm::vec2>& getVertices() const {
            return this->vertices;
        }
        
        float getRadius() const {
            return this->radius;
        }
        
        int getSegments() const {
            return this->segments;
        }
        
        // Converting from degrees to radians
        // radians = (degrees * pi) / 180;
        static float toRadians(float _angle){
            return _angle * M_PI / 180.0;
        }
        
    private:
        float radius;
        int segments;
        
        std::vector<glm::vec2> vertices;
    };

    
	Torus::Torus() : Shape()
	{
        float radiusX = 1.0; // radius in xz-plane (main radius)
        float radiusY = 0.3; // radius in xy-plane (radius of the ring segments)
        int segmentsInXZPlane = 50; // subdivision in xz-plane (amount of ring segments)
        int segmentsInXYPlane = 30; // subdivision in xy-plane
        
		std::vector<glm::vec3> midPoints;
		std::vector<float> midPointsLenght;

        Circle circleXZ(radiusX, segmentsInXZPlane);
        Circle circleXY(radiusY, segmentsInXYPlane);
        
        // calculate positions
		for (int j = 0; j < circleXZ.getSegments(); j++)
		{
			for (int i = 0; i < circleXY.getVertices().size(); i++)
			{
                glm::vec3 currentPoint(circleXZ.getVertices()[j].x, 0.0, circleXZ.getVertices()[j].y);
				glm::vec3 dirExtension = glm::normalize(currentPoint) * circleXY.getVertices()[i].x;
                currentPoint.y = circleXY.getVertices()[i].y;
				this->positions.push_back(currentPoint + dirExtension);
			}
		}

		// calculate faces
		for (int j = 0; j < circleXZ.getSegments(); j++)
		{
			int startIdx = j * circleXY.getSegments();
            if (j + 1 == circleXZ.getSegments()) {
                // special case for connecting the last ring segments
                for (int i = 0; i < circleXY.getSegments(); i++)
                {
                    int currIdx = startIdx + i;
                    int firstSegIdx = i;
                    if (i + 1 == circleXY.getSegments()) {
                        this->addTwoFaces(currIdx, firstSegIdx, startIdx, 0);
                    } else {
                        this->addTwoFaces(currIdx, firstSegIdx, currIdx + 1, firstSegIdx + 1);
                    }
                }
            }else{
                // this parts connects all ring segments
                for (int i = 0; i < circleXY.getSegments(); i++)
                {
                    int currIdx = startIdx + i;
                    // special case for the last two faces of a single ring segment
                    if (i + 1 == circleXY.getSegments()) {
                        this->addTwoFaces(currIdx, currIdx + circleXY.getSegments(), startIdx, startIdx + circleXY.getSegments());
                    } else { 
                        this->addTwoFaces(currIdx, currIdx + circleXY.getSegments(), currIdx + 1, currIdx + 1 + circleXY.getSegments());
                    }
                }
            }
		}

		// just color the object from black to green
		for (int i = 0; i < this->positions.size(); i++) {
			this->colors.push_back(glm::vec3(0.06, 0.55, 0.31));
		}

        // optional: adding face normals
		for (int i = 0; i < this->faces.size(); i++) {
			glm::vec3 v1 = this->positions[this->faces[i].y] - this->positions[this->faces[i].x];
			glm::vec3 v2 = this->positions[this->faces[i].z] - this->positions[this->faces[i].x];
			this->faceNormals.push_back(glm::normalize(glm::cross(v1, v2)));
		}
        
		// optional: adding normals
		for (int i = 0; i < this->positions.size(); i++) {
			std::vector<unsigned int> faceids;
			// find the face ids with this vertex
			for (int j = 0; j < this->faces.size(); j++) {
				if (i == this->faces[j].x || i == this->faces[j].y || i == this->faces[j].z) {
					faceids.push_back(j);
				}	
			}
			// sum up the face normals and divide it by the lenght of the summed up vector
			glm::vec3 vSum(0.0, 0.0, 0.0);
			for (int j = 0; j < faceids.size(); j++) {
				vSum += this->faceNormals[faceids[j]];
			}
			vSum /= glm::length(vSum);
			this->normals.push_back(vSum);
		}

		// TODO: set the texture coordinates for the torus
		//       first thing here is to think about how you want to map the texture
		//       on the torus. I decided that the texture should appear 4 times on the torus,
		//       but you can do that how you want. Remember that you can do the repetition of 
		//       the same texture either by setting the texture coordinates between 0.0 and 1.0
		//       or by using one of the texture functions, e.g. with GL_REPEAT

		//this->texCoords...

        // calculate positions
		for (int j = 0; j < circleXZ.getSegments(); j++)
		{
			for (int i = 0; i < circleXY.getVertices().size(); i++)
			{
                this->texCoords.push_back(
                    glm::vec2(float(i)/circleXY.getVertices().size(),float(j)/circleXZ.getSegments())
                );
			}
        }
		// END TO
	}
    
    void Torus::addTwoFaces(unsigned int _idx0,unsigned int  _idx1,unsigned int  _idx2,unsigned int  _idx3)
    {
        this->faces.push_back(glm::uvec3(_idx0, _idx2, _idx1));
        this->faces.push_back(glm::uvec3(_idx2, _idx3, _idx1));
    }
}
