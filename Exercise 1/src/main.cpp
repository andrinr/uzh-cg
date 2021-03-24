#ifndef ExampleMain_h
#define ExampleMain_h

#include "GLExample.h"

int main(int argc, char *argv[])
{
    if(argv[0] != nullptr) {
		// get path to executable from command line argument
        std::string exePath(argv[0]);
		// extract the folder where the executable is. For us usually /build/<configuration>
        exePath = exePath.substr(0, exePath.find_last_of("/\\")+1);
		// create the app
        cgCourse::GLExample app(glm::uvec2(800, 600), std::string("OpenGL Example"), exePath);
        // run the app
    	app.run();
		// exit if the app is finished. 
        exit(0);
    }else{
        std::cout << "You might need to specify argv[0] somehow: " << argv[0] << std::endl;
    }
}

#endif
