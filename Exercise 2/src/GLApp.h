#ifndef Example2_GLApp_h
#define Example2_GLApp_h

#include "GLIncludes.h"
#include <glm/vec2.hpp>
#include <string>

namespace cgCourse
{
	class GLApp
	{
	public:
		GLApp(glm::uvec2 _windowSize, std::string _title, std::string _exepath, bool resizeable = true);
		virtual ~GLApp();

		bool run();

		// Default implementation of event handlers
		virtual void keyPressHandler(int key, int action, int mods);
		virtual void mouseClickHandler(int button, int action);
		virtual void mouseMoveHandler(glm::dvec2 position);

        std::string getPathToExecutable() const;
	protected:
		void stop();

		// Virtual methods for initialization, rendering and termination
		virtual bool init() = 0;
		virtual bool render() = 0;
		virtual bool end() = 0;

		// Utility methods
		glm::uvec2 getFramebufferSize() const;
		std::string loadFile(const std::string & filename) const;
		bool checkGlError(const char* message) const;

		GLFWwindow* window_;
		std::string const title;
        std::string const pathToExecutable;
	};
}


#endif
