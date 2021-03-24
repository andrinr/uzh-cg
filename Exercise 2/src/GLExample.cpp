#include "GLExample.h"
#include "Cube.h"
#include <iostream>

namespace cgCourse
{
	GLExample::GLExample(glm::uvec2 _windowSize, std::string _title, std::string _exepath)
		: GLApp(_windowSize, _title, _exepath, false)
	{
		program = 0;
		mvpUniformLocation = 0;
		this->mvpMatrix = glm::mat4();
	}

	bool GLExample::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		glm::uvec2 fbSize = getFramebufferSize();
		glViewport(0, 0, int(fbSize.x), int(fbSize.y));
        
        // load shader source code
		std::string vertShaderString = this->loadFile(this->getPathToExecutable() + "../../src/Cube.vert");
		std::string fragShaderString = this->loadFile(this->getPathToExecutable() + "../../src/Cube.frag");

		// Build and compile our shader program consisting of 
		// a vertex and fragment shader
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		loadAndCompileShaderToGPU(vertShader, vertShaderString);
		loadAndCompileShaderToGPU(fragShader, fragShaderString);
		
		// Link shaders
		this->program = glCreateProgram();
		// check if it exists
		assert(this->program);
		// attach the shaders to the shader program
		glAttachShader(this->program, vertShader);
		glAttachShader(this->program, fragShader);
		// link the program to make it ready to use by the GPU
		glLinkProgram(this->program);
		// check the link status of the program and show linking errors
		// if there are any
		this->checkLinkStatusOfProgram(this->program);
		
		// shader programs can be marked as to delete. We don't have
		// to do this here if it is done later anywhen in the program. An explanation is here:
		// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml
        //
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		// Get uniform locations for our mvp matrix
		mvpUniformLocation = glGetUniformLocation(this->program, "mvpMatrix");

		// Init models
		this->cube = std::make_shared<Cube>();
		bool constructed = this->cube->createVertexArray(0, 1, 2);
		if (!constructed) return constructed;
		this->cube->setShapePosition(glm::vec3(-2.0, 0.0,0.0));

		// Init models
		this->cuboid = std::make_shared<Cuboid>();
		constructed = this->cuboid->createVertexArray(0, 1, 2);
		this->cuboid->setShapePosition(glm::vec3(1.0, 0.0, 0.0));
		return constructed;
	}

	bool GLExample::render()
	{
		glEnable(GL_DEPTH_TEST);
        
        // Clear the color and depth buffers
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
		/* TODO: Add here code for the following tasks:
		 *    - enable or disable face culling.
		 *    - change between front face and backface culling.
		 *    - change the ordering of vertices/indices in triangles to be considered for front face and backface culling.
		 *    - enable or disable wireframe mode
		 *
		 * All these things can be done with one line of code. The main task is to find the commands and 
		 * apply the parameters. There are several ressource where you can find this information 
		 * e.g. OpenGL reference, official OpenGL specification or a OpenGL cheatsheet
		 */


		//...

		glEnable(GL_CULL_FACE);  	
		glCullFace(GL_FRONT);  
		//glCullFace(GL_BACK);
		//glCullFace(GL_FRONT_AND_BACK);

		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		/* END TODO */

		// Load program
		glUseProgram(this->program);

		// compute (currently) static matrix for the camera
		glm::mat4 viewProjectionMatrix = this->computeViewProjectionMatrix();

		// calculate model matrix for the cube object and set the uniform to store it in the shader
		this->mvpMatrix = viewProjectionMatrix * this->cube->getModelMatrix();
		glUniformMatrix4fv(this->mvpUniformLocation, 1, GL_FALSE, &this->mvpMatrix[0][0]);
		// bind the Vertex Array Object of the cube and draw the triangles
		glBindVertexArray(this->cube->getVertexArrayId());
		glDrawElements(this->cube->getDrawElemType(), this->cube->getDrawElemCount(),
			GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		/* TODO: Add here code to call the draw method of the cuboid similar to the cube above */
		
		// ...
		this->mvpMatrix = viewProjectionMatrix * this->cuboid->getModelMatrix();
		glUniformMatrix4fv(this->mvpUniformLocation, 1, GL_FALSE, &this->mvpMatrix[0][0]);
		// bind the Vertex Array Object of the cube and draw the triangles
		glBindVertexArray(this->cuboid->getVertexArrayId());
		glDrawElements(this->cuboid->getDrawElemType(), this->cuboid->getDrawElemCount(),
			GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		/* END TODO */

		return true;
	}

	bool GLExample::end()
	{
		if (this->program)
		{
			glDeleteProgram(this->program);
		}
		return true;
	}

	bool GLExample::loadAndCompileShaderToGPU(GLuint _program, std::string _source) {
		GLint status;
		GLchar errorMessage[512];

		char* shadersource = (char *)_source.c_str();
		int shaderstringlength = _source.length();
		glShaderSource(_program, 1, (const GLchar **)&shadersource, &shaderstringlength);
		glCompileShader(_program);
		glGetShaderiv(_program, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			glGetShaderInfoLog(_program, 512, 0, errorMessage);
			std::cerr << "Fragment Shader compilation error:" << std::endl
				<< errorMessage << std::endl;
			return false;
		}
		return true;
	}

	bool GLExample::checkLinkStatusOfProgram(GLuint _program) {
		GLint status;
		GLchar errorMessage[512];
		glGetProgramiv(_program, GL_LINK_STATUS, &status);
		if (!status) {
			glGetProgramInfoLog(_program, 512, 0, errorMessage);
			std::cerr << "Linking error:" << std::endl
				<< errorMessage << std::endl;
			return false;
		}
		return true;
	}

	glm::mat4 GLExample::computeViewProjectionMatrix() const
	{
		// Camera matrix
		glm::mat4 view = glm::lookAt(
			glm::vec3(-1, 5, -16), // Camera is at (-1, 18, -18), in World Space
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

