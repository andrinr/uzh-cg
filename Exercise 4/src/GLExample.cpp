#include "GLExample.h"
#include "Cube.h"
#include <iostream>

namespace cgCourse
{
	GLExample::GLExample(glm::uvec2 _windowSize, std::string _title, std::string _exepath)
		: GLApp(_windowSize, _title, _exepath, false)
	{
		this->mvpMatrix = glm::mat4();
		this->animation = 0.0;
		this->animationDir = Forward;
		this->drawTorusNormals = false; // just in case somebody wants to activate the normals
	}

	bool GLExample::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		// setup camera with standard view (static for our case)
		this->cam.create(this->getFramebufferSize(),
						 glm::vec3(3, 3, -3),
						 glm::vec3(0, 0, 0),
						 glm::vec3(0, 1, 0));

		programForCube = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Cube");
		programForTorus = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Torus");
		programForTorusNormals = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Normals");
		programForLightBox = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Lightbox");

		// create box for light position
		this->lightbox = std::make_shared<Cube>();
		if (!this->lightbox->createVertexArray(0, 1, 2))
		{
			return false;
		};
		this->lightbox->setPosition(glm::vec3(0.0, 0.5, -1.5));
		this->lightbox->setScaling(glm::vec3(0.1, 0.1, 0.1));
		this->lightboxColor = glm::vec3(1.0, 1.0, 1.0);

		// Init models
		this->cube = std::make_shared<Cube>();
		bool constructed = this->cube->createVertexArray(0, 1, 2);
		if (!constructed)
			return constructed;
		this->cube->setPosition(glm::vec3(-2.5, 0.0, -1.0));
		this->cube->setScaling(glm::vec3(1.0, 2.0, 1.0));

		this->torus = std::make_shared<Torus>();
		constructed = this->torus->createVertexArray(0, 1, 2);
		this->torus->setPosition(glm::vec3(1.5, 0.0, 0.0));

		// Init multiline field for normals of objects
		this->normalsTorus = std::make_shared<MultiLine>(this->torus->getPositions(),
														 this->torus->getNormals());
		constructed = this->normalsTorus->createVertexArray(0, 1, 2);
		this->normalsTorus->setPosition(glm::vec3(1.0, 0.0, 0.0));

		/* TODO set light info here */
		// this->light.ambientTerm ...
		this->light.ambientTerm = glm::vec3(0.1,0.1,0.1);
		this->light.diffuseTerm = glm::vec3(0.6,0.6,0.6);
		this->light.specularTerm = glm::vec3(0.8,0.8,0.8);
		// End
		return constructed;
	}

	bool GLExample::update()
	{
		this->torus->setRotation(glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if (animationDir == Forward)
		{
			if (animation > 5.0)
			{
				animationDir = Backward;
			}
			else
			{
				animation += 0.01;
			}
		}
		else
		{
			if (animation < -1.5)
			{
				animationDir = Forward;
			}
			else
			{
				animation -= 0.01;
			}
		}
		this->lightbox->setPosition(glm::vec3(0.0, 0.5, animation));
		return true;
	}

	bool GLExample::render()
	{
		glEnable(GL_DEPTH_TEST);

		// Clear the color and depth buffers
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		this->renderLightBox();

		this->addLightVariables(programForCube);
		this->addLightVariables(programForTorus);

		this->renderCubes();
		this->renderTorus();
		return true;
	}

	/* TODO update this function to set the light information for the cube and the torus
	 * shaders. Don't forget that shader have to be bound before shader uniform can be set..
	 */
	void GLExample::addLightVariables(const std::shared_ptr<ShaderProgram> &_program)
	{
		glUniform3f(
			_program->getUniformLocation("lightPosition"),
			this->lightbox->getPosition()[0],
			this->lightbox->getPosition()[1],
			this->lightbox->getPosition()[2]
		);


		glUniform3f(
			_program->getUniformLocation("lightColor"),
			this->lightboxColor[0],
			this->lightboxColor[1],
			this->lightboxColor[2]
		);

		glUniform3f(
			_program->getUniformLocation("ambientTerm"),
			this->light.ambientTerm[0], 
			this->light.ambientTerm[1], 
			this->light.ambientTerm[2]
		);

		glUniform3f(
			_program->getUniformLocation("diffuseTerm"),
			this->light.diffuseTerm[0], 
			this->light.diffuseTerm[1], 
			this->light.diffuseTerm[2]
		);

		glUniform3f(
			_program->getUniformLocation("specularTerm"),
			this->light.specularTerm[0], 
			this->light.specularTerm[1], 
			this->light.specularTerm[2]
		);

		glUniform3f(
			_program->getUniformLocation("viewerPosition"),
			this->cam.getPosition()[0],
			this->cam.getPosition()[1],
			this->cam.getPosition()[2]
		);
	}
	// END TODO

	/* TODO update this function as well to set the light information for the cube shaders */
	void GLExample::renderCubes()
	{
		programForCube->bind();
		this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->cube->getModelMatrix();
		glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1, GL_FALSE, &this->cube->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
		this->addLightVariables(programForCube);
		this->cube->draw();
		programForCube->unbind();

		this->cube->setPosition(glm::vec3(-2.5, 0.0, 1.5));

		programForCube->bind();
		this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->cube->getModelMatrix();
		glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1, GL_FALSE, &this->cube->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
		this->addLightVariables(programForCube);
		this->cube->draw();
		programForCube->unbind();

		this->cube->setPosition(glm::vec3(-2.5, 0.0, 4.0));

		programForCube->bind();
		this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->cube->getModelMatrix();
		glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1, GL_FALSE, &this->cube->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
		this->addLightVariables(programForCube);
		this->cube->draw();
		programForCube->unbind();

		this->cube->setPosition(glm::vec3(-2.5, 0.0, 6.5));

		programForCube->bind();
		this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->cube->getModelMatrix();
		glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1, GL_FALSE, &this->cube->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
		this->addLightVariables(programForCube);
		this->cube->draw();
		programForCube->unbind();

		this->cube->setPosition(glm::vec3(-2.5, 0.0, -1.0));
	}
	// END TODO

	void GLExample::renderTorus()
	{
		programForTorus->bind();
		this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->torus->getModelMatrix();
		glUniformMatrix4fv(programForTorus->getUniformLocation("modelMatrix"), 1, GL_FALSE, &this->torus->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForTorus->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
		this->addLightVariables(programForTorus);
		this->torus->draw();
		programForTorus->unbind();

		// draw torus normals
		if (drawTorusNormals)
		{
			programForTorusNormals->bind();
			this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->torus->getModelMatrix();
			glUniformMatrix4fv(programForTorusNormals->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
			this->normalsTorus->draw();
			programForTorusNormals->unbind();
		}
	}

	void GLExample::renderLightBox()
	{
		programForLightBox->bind();
		this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->lightbox->getModelMatrix();
		glUniform3fv(programForLightBox->getUniformLocation("objectColor"), 1, &this->lightboxColor[0]);
		glUniformMatrix4fv(programForLightBox->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
		this->lightbox->draw();
		programForLightBox->unbind();
	}

	bool GLExample::end()
	{
		programForCube->deleteShaderProgramFromGPU();
		programForTorus->deleteShaderProgramFromGPU();
		programForTorusNormals->deleteShaderProgramFromGPU();
		return true;
	}
}
