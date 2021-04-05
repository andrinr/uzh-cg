#include "GLExample.h"
#include "Cube.h"
#include <iostream>
#include <chrono>


namespace cgCourse
{
	GLExample::GLExample(glm::uvec2 _windowSize, std::string _title, std::string _exepath)
		: GLApp(_windowSize, _title, _exepath, false)
	{
		this->mvpMatrix = glm::mat4();
	}

	bool GLExample::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		glm::uvec2 fbSize = getFramebufferSize();
		glViewport(0, 0, int(fbSize.x), int(fbSize.y));
        
        programForCube = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Cube");
        programForTorus = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Torus");
		programForTorusNormals = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Normals");

		// Init models
		this->cube = std::make_shared<Cube>();
		bool constructed = this->cube->createVertexArray(0, 1, 2);
		if (!constructed) return constructed;
        
		this->cube->setPosition(glm::vec3(-2.0, 0.0, 1.0));
        this->cube->setScaling(glm::vec3(1.0, 1.0, 3.0));

		this->torus = std::make_shared<Torus>();
		constructed = this->torus->createVertexArray(0, 1, 2);
		this->torus->setPosition(glm::vec3(1.0, 0.0, 0.0));
        
        // Init multiline field for normals of objects
        this->normalsTorus = std::make_shared<MultiLine>(this->torus->getPositions(),
                                                         this->torus->getNormals());
        constructed = this->normalsTorus->createVertexArray(0, 1, 2);
        this->normalsTorus->setPosition(glm::vec3(1.0, 0.0, 0.0));
        
        return constructed;
	}

    bool GLExample::update()
    {
		this->torus->setRotation(0.001, {1,0.8,0.4});
		this->cube->setRotation(0.002, {0.4,1.0,0.8});

        return true;
    }
	
	bool GLExample::render()
	{
		glEnable(GL_DEPTH_TEST);
        
        // Clear the color and depth buffers
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

		// compute view and projection matrix for the camera (static for our case)
		this->viewProjectionMatrix = this->computeViewProjectionMatrix();
        
        this->renderCube();
        this->renderTorus();
		return true;
	}
    
    void GLExample::renderCube() {
        programForCube->bind();
        this->mvpMatrix = this->viewProjectionMatrix * this->cube->getModelMatrix();
        glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
        this->cube->draw();
        programForCube->unbind();
    }
    
    void GLExample::renderTorus(){
        programForTorus->bind();
		this->mvpMatrix = this->viewProjectionMatrix * this->torus->getModelMatrix();

		// There is some error in normal matrix. Either here or in the torus.vert shader
		glm::mat4 normalMatrix = glm::transpose(glm::inverse(this->mvpMatrix));
		glUniformMatrix4fv(programForTorus->getUniformLocation("normMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);

		glUniformMatrix4fv(programForTorus->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
        this->torus->draw();
        programForTorus->unbind();
        
		// Uncomment to add normal lines

		/*programForTorusNormals->bind();
		this->mvpMatrix = this->viewProjectionMatrix * this->normalsTorus->getModelMatrix();

		glUniformMatrix4fv(programForTorusNormals->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
        this->normalsTorus->draw();
        programForTorusNormals->unbind();*/
    }
    
	bool GLExample::end()
	{
        programForCube->deleteShaderProgramFromGPU();
        programForTorus->deleteShaderProgramFromGPU();
		programForTorusNormals->deleteShaderProgramFromGPU();
		return true;
	}

	glm::mat4 GLExample::computeViewProjectionMatrix() const
	{
		// Camera matrix
		glm::mat4 view = glm::lookAt(
			glm::vec3(3, 3, -3), // Camera is at (0,0,-3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);

		// Projection matrix
		float fieldOfView = 45.0f;
		float nearPlane = 0.1;
		float farPlane = 50.0;
		glm::uvec2 fbSize = getFramebufferSize();
		float aspect = float(fbSize.x) / float(fbSize.y);

		glm::mat4 projection = glm::perspective(fieldOfView, aspect,
			nearPlane, farPlane);

		return projection * view;
	}
}

