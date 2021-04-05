#ifndef Example_GLExample_h
#define Example_GLExample_h

#include "GLApp.h"
#include "Cube.h"
#include "Torus.h"
#include "ShaderProgram.h"
#include "MultiLine.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <chrono>

namespace cgCourse
{
	class GLExample : public GLApp
	{
	public:
		enum MotionMode {
			NoMotionMode = 0, RotateMode = 1, TranslateMode = 2, ZoomMode = 3
		};

		GLExample(glm::uvec2 _windowSize, std::string _title, std::string _exepath);

		bool init() override;
        bool update() override;
		bool render() override;
		bool end() override;

	private:
        void renderCube();
        void renderTorus();
        
        glm::mat4 computeViewProjectionMatrix() const;

		glm::mat4 mvpMatrix;
        glm::mat4 viewProjectionMatrix;
        
        std::shared_ptr<ShaderProgram> programForCube;
        std::shared_ptr<ShaderProgram> programForTorus;
		std::shared_ptr<ShaderProgram> programForTorusNormals;
		std::shared_ptr<Cube> cube;
		std::shared_ptr<Torus> torus;
        std::shared_ptr<MultiLine> normalsTorus;
	};
}

#endif
