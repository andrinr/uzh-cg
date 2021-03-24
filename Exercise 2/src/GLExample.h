#ifndef Example2_GLExample_h
#define Example2_GLExample_h

#include "GLApp.h"
#include "Cube.h"
#include "Cuboid.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

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
		bool render() override;
		bool end() override;

	private:
		bool loadAndCompileShaderToGPU(GLuint _program, std::string _source);
		glm::mat4 computeViewProjectionMatrix() const;
		bool checkLinkStatusOfProgram(GLuint _program);

		GLuint program;
		GLuint mvpUniformLocation;
		glm::mat4 mvpMatrix;
		std::shared_ptr<Cube> cube;
		std::shared_ptr<Cuboid> cuboid;
	};
}

#endif
