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
		if (!this->lightbox->createVertexArray(0, 1, 2, 3 )) {
			return false;
		};
		this->lightbox->setPosition(glm::vec3(0.0, 0.5, -1.5));
		this->lightbox->setScaling(glm::vec3(0.05, 0.05, 0.05));
		this->lightboxColor = glm::vec3(1.0, 1.0, 1.0);

		// Init models
		this->cube = std::make_shared<Cube>();
		bool constructed = this->cube->createVertexArray(0, 1, 2, 3);
		if (!constructed) return constructed;
		this->cube->setPosition(glm::vec3(-2.5, 0.5, 1.5));
        this->cube->setScaling(glm::vec3(1.5, 1.5, 1.5));

		this->torus = std::make_shared<Torus>();
		constructed = this->torus->createVertexArray(0, 1, 2, 3);
		this->torus->setPosition(glm::vec3(1.5, 0.0, 0.0));
        
        // Init multiline field for normals of objects
        this->normalsTorus = std::make_shared<MultiLine>(this->torus->getPositions(),
                                                         this->torus->getNormals());
        constructed = this->normalsTorus->createVertexArray(0, 1, 2, 3);
        this->normalsTorus->setPosition(glm::vec3(1.0, 0.0, 0.0));
        
		this->light.ambientTerm = glm::vec3(1.0, 1.0, 1.0);
		this->light.diffuseTerm = glm::vec3(1.0, 1.0, 1.0);
		this->light.specularTerm = glm::vec3(1.0, 1.0, 1.0);

		/* TODO: load the following textures here:
		 *       - cubetex - the diffuse texture
		 *       - cubetexSpec - the specular map
		 *       - torustex - the diffuse texture for the torus
		 *       - torustexSpec - the specular map for the torus
		 *      The easist thing will be if you start with the diffuse
		 *      texture for the cube. Don't forget to initialize the shared pointers existing 
		 *      already in this class for this purpose.     
		 */
		this->cubetex = std::make_shared<Texture>();
		this->cubetex->loadFromFile(this->getPathToExecutable() + "../../res/Metal_Trimsheet_001_basecolor.jpg");

		this->cubetexSpec = std::make_shared<Texture>();
		this->cubetexSpec->loadFromFile(this->getPathToExecutable() + "../../res/Metal_Trimsheet_001_metallic.jpg");

		this->torustex = std::make_shared<Texture>();
		this->torustex->loadFromFile(this->getPathToExecutable() + "../../res/Sci-Fi_Padded_Fabric_004_baseColor.jpg");

		this->torustexSpec = std::make_shared<Texture>();
		this->torustexSpec->loadFromFile(this->getPathToExecutable() + "../../res/Sci-Fi_Padded_Fabric_004_metallic.jpg");
		//...

		// End TODO

        return constructed;
	}

    bool GLExample::update()
    {
		this->torus->setRotation(glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if(animationDir == Forward)
		{
			if (animation > 1.5) {
				animationDir = Backward;
			} else {
				animation += 0.01;
			}
		} else {
			if (animation < -3.0) {
				animationDir = Forward;
			}
			else {
				animation -= 0.01;
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
		/* TODO: bind textures for shaders with glBindTexture and glActiveTexture. 
		 *       check the OpenGL documentation to understand these commands.
		 *       Also, remember that you will have to set the uniform variables in
		 *       the shader correctly as well so that the program know which uniform 
		 *       variable in the shader is meant to be which texture layer when 
		 *       used with glActiveTexture.
		 */
		
		this->cubetex->bind();
		glActiveTexture(this->cubetex->getTexHandle());
		GLint texDiff = programForCube->getUniformLocation("texDiff");
		glUniform1i(texDiff, 0);

		this->cubetexSpec->bind();
		glActiveTexture(this->cubetexSpec->getTexHandle());
		GLint texSpec = programForCube->getUniformLocation("texSpec");
		glUniform1i(texSpec, 0);


		// End TODO

        this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->cube->getModelMatrix();
		glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1, GL_FALSE, &this->cube->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
        this->cube->draw();

		/* TODO: unbind textures by setting all glBindTextures for all active texture layers 
		 *       to zero.
		 */
		this->cubetex->unbind();
		this->cubetexSpec->unbind();
		


		// End TODO
        programForCube->unbind();
    }

    void GLExample::renderTorus(){
        programForTorus->bind();
		/* TODO: apply the texture and the specular map for the torus as well 
		 *       analogue to the function above.
		*/

		this->torustex->bind();
		glActiveTexture(this->cubetex->getTexHandle());
		GLint texDiff = programForCube->getUniformLocation("texDiff");
		glUniform1i(texDiff, 0);

		this->torustexSpec->bind();
		glActiveTexture(this->cubetexSpec->getTexHandle());
		GLint texSpec = programForCube->getUniformLocation("texSpec");
		glUniform1i(texSpec, 0);
		


		// End TODO

		this->mvpMatrix = this->cam.getViewProjectionMatrix() * this->torus->getModelMatrix();
		glUniformMatrix4fv(programForTorus->getUniformLocation("modelMatrix"), 1, GL_FALSE, &this->torus->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForTorus->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &this->mvpMatrix[0][0]);
        this->torus->draw();
        programForTorus->unbind();
        
		/* TODO: unbind textures by setting all glBindTextures for all active texture layers
		*       to zero.
		*/
		
		this->cubetex->unbind();
		this->cubetexSpec->unbind();
		

		// End TODO

		// draw torus normals
		if(drawTorusNormals)
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

