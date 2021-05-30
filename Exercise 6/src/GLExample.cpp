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
		this->drawTorusNormals = false; // enable to activate the normals
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
		if (!this->lightbox->createVertexArray(0, 1, 2, 3, 4 )) {
			return false;
		};
		this->lightbox->setPosition(glm::vec3(0.0, 0.5, -1.0));
		this->lightbox->setScaling(glm::vec3(0.05, 0.05, 0.05));
		this->lightboxColor = glm::vec3(1.0, 1.0, 1.0);

		// Init models
		this->cube = std::make_shared<Cube>();
		bool constructed = this->cube->createVertexArray(0, 1, 2, 3, 4);
		if (!constructed) return constructed;
		this->cube->setPosition(glm::vec3(-2.5, 0.5, 1.5));
        this->cube->setScaling(glm::vec3(1.5, 1.5, 1.5));

		this->torus = std::make_shared<Torus>();
		constructed = this->torus->createVertexArray(0, 1, 2, 3, 4);
		this->torus->setPosition(glm::vec3(1.5, 0.0, 0.0));
        
        // Init multiline field for normals of objects
        if(this->torus->getNormals().size() > 0) {
            this->normalsTorus = std::make_shared<MultiLine>(this->torus->getPositions(), this->torus->getNormals());
            constructed = this->normalsTorus->createVertexArray(0, 1, 2, 3, 4);
            this->normalsTorus->setPosition(glm::vec3(1.0, 0.0, 0.0));
        }

		this->light.ambientTerm = glm::vec3(1.0, 1.0, 1.0);
		this->light.diffuseTerm = glm::vec3(1.0, 1.0, 1.0);
		this->light.specularTerm = glm::vec3(1.0, 1.0, 1.0);

		/* TODO: load the following textures here:
		 *       - cubeNormaltex - the normal texture for the cube 
		 *       - torusNormaltex - the normal texture for the torus 
		 *       It is also possible to use the brickwall for the cube, may be it is easier to debug.
		 */


        
        // End TODO
        
		this->cubetex = std::make_shared<Texture>();
		this->cubetex->loadFromFile(this->getPathToExecutable() + "../../res/container.png");
		this->cubetexSpec = std::make_shared<Texture>();
        this->cubetexSpec->loadFromFile(this->getPathToExecutable() + "../../res/container_specular.png");
		this->cubeNormaltex = std::make_shared<Texture>();
        this->cubeNormaltex->loadFromFile(this->getPathToExecutable() + "../../res/container_normal.jpg");

        this->torustex = std::make_shared<Texture>();
		this->torustex->loadFromFile(this->getPathToExecutable() + "../../res/brickwall.jpg");
		this->torustexSpec = std::make_shared<Texture>();
		this->torustexSpec->loadFromFile(this->getPathToExecutable() + "../../res/brickwall_specular.jpg");
		this->torusNormaltex = std::make_shared<Texture>();
        this->torusNormaltex->loadFromFile(this->getPathToExecutable() + "../../res/brickwall_normal.jpg");

        return constructed;
	}

    bool GLExample::update()
    {
		this->torus->setRotation(glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if(animationDir == Forward)
		{
			if (animation > 1.5) {
				animationDir = Backward;
			} else {
				animation += 0.002;
			}
		} else {
			if (animation < -4.0) {
				animationDir = Forward;
			}
			else {
				animation -= 0.002;
			}
		}
		this->lightbox->setPosition(glm::vec3(animation, 0.5, -0.5));
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

	void GLExample::addLightVariables(const std::shared_ptr<ShaderProgram>& _program) {
		_program->bind();
		glUniform3fv(_program->getUniformLocation("camPos"), 1, &this->cam.getPosition()[0]);
		glUniform3fv(_program->getUniformLocation("light.position"), 1, &lightbox->getPosition()[0]);
		glUniform3fv(_program->getUniformLocation("light.ambient"), 1, &this->light.ambientTerm[0]);
		glUniform3fv(_program->getUniformLocation("light.diffuse"), 1, &this->light.diffuseTerm[0]);
		glUniform3fv(_program->getUniformLocation("light.specular"), 1, &this->light.specularTerm[0]);
		_program->unbind();
	}

    void GLExample::renderCubes() {
        programForCube->bind();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->cubetex->getTexHandle());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->cubetexSpec->getTexHandle());
		glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, this->cubeNormaltex->getTexHandle());
        
        glUniform1i(programForCube->getUniformLocation("cubetex"), 0);
        glUniform1i(programForCube->getUniformLocation("cubetexSpec"), 1);
        
		/* TODO: bind the normal map textures for shaders with glBindTexture and glActiveTexture.
		 *       check the OpenGL documentation to understand these commands.
		 *       Also, remember that you will have to set the uniform variables in
		 *       the shader correctly as well so that the program know which uniform 
		 *       variable in the shader is meant to be which texture layer when 
		 *       used with glActiveTexture.
		 */
        glUniform1i(programForCube->getUniformLocation("cubeNormaltex"), 2);

		// End TODO

        this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->cube->getModelMatrix();
		glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1, GL_FALSE, &this->cube->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
        this->cube->draw();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        
		/* TODO: unbind textures by setting all glBindTextures for all active texture layers 
		 *       to zero.
		 */
		glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        

		// End TODO
        programForCube->unbind();
    }

    void GLExample::renderTorus(){
        programForTorus->bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->torustex->getTexHandle());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, this->torustexSpec->getTexHandle());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, this->torusNormaltex->getTexHandle());

		glUniform1i(programForTorus->getUniformLocation("torustex"), 0);
		glUniform1i(programForTorus->getUniformLocation("torustexSpec"), 1);
		// End TODO
        
		/* TODO: apply the normal map for the torus as well
		*       analogue to the function above.
		*/
		glUniform1i(programForTorus->getUniformLocation("torusNormaltex"), 2);


        // End TODO
        
		this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->torus->getModelMatrix();
		glUniformMatrix4fv(programForTorus->getUniformLocation("modelMatrix"), 1, GL_FALSE, &this->torus->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForTorus->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
        this->torus->draw();
        programForTorus->unbind();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        /* TODO: unbind textures by setting all glBindTextures for all active texture layers
         *       to zero.
         */
		glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
        

        // End TODO

		// draw torus normals
		if(true)
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
		glUniform3fv(programForLightBox->getUniformLocation("objectColor"), 1,&this->lightboxColor[0]);
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

