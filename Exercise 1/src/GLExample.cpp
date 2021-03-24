#include "GLExample.h"

namespace cgCourse
{
	GLExample::GLExample(glm::uvec2 _windowSize, std::string _title, std::string _exepath)
		: GLApp(_windowSize, _title, _exepath, false)
	{
		program = 0;
		mvpUniformLocation = 0;
		this->mvpMatrix = glm::mat4();
		this->cube = std::make_shared<Cube>();
	}

	bool GLExample::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		glm::uvec2 fbSize = getFramebufferSize();
		glViewport(0, 0, int(fbSize.x), int(fbSize.y));
        
        // load shader source code
		std::string vertShaderString = this->loadFile(this->getPathToExecutable()+"../../src/Cube.vert");
		std::string fragShaderString = this->loadFile(this->getPathToExecutable()+"../../src/Cube.frag");

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
		return this->cube->createVertexArray(0, 1, Model::InvalidAttribLoc);
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

	bool GLExample::render()
	{
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		// Clear the color and depth buffers
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Load program
		glUseProgram(this->program);

		// Set matrices
		this->computeMvpMatrix();
		glUniformMatrix4fv(this->mvpUniformLocation, 1, GL_FALSE, &this->mvpMatrix[0][0]);

		glBindVertexArray(this->cube->getVertexArrayId());
		glDrawElements(this->cube->getDrawElemType(), this->cube->getDrawElemCount(),
			GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

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

	void GLExample::computeMvpMatrix()
	{
		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 model = glm::mat4();

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

		this->mvpMatrix = projection * view * model;
	}
}

