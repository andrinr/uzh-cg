OpenGL (Open Graphics Library) is a cross-platform application programming interface (API) for rendering 2D and 3D graphics. It was initially released by Silicon Graphics Inc. (SGI) in 1992 and is still today the most widely adopted cross-platform API for hardware-accelerated rendering.

In this exercise, you have to compile and run an OpenGL example coded in C++ and change the background color to a custom color. It is a simple example using only basic functionality from OpenGL and the GLFW library for the cross-platform helper functions.

----
What you need to get it running:

IDE & C++ compiler: Visual Studio with C++ installed (Win), Xcode (OSX) or some IDE with gcc (Linux) installed, for example QT Creator. We use Windows or OSX for these example, so it might be additional effort in case you want to use a Linux system. However, most of the things should compile under Linux as well.  

CMake: you can use the most recent version of cmake.

Libaries GLFW & GLEW:

We need a couple of libaries, specifically GLFW and GLEW.

Win: Under Windows with Visual Studio 2013 or newer, the prebuilt packages for those libaries come with the example and it should work out of the box. I would suggest you download the Visual Studio MSDNAA version for students. For Visual Studio 2017 you have to modify your installation so that it includes the VC++ 2015 package as well. Please write in the forum if you have troubles with a certain configuration. 

OSX: The OSX packages can be installed with homebrew. If you don't have homebrew please install it first according to the website. Afterwards you should be able to make:

brew install glfw3

brew install glew

Linux: glfw3 packages and glew packages should be available under linux as well. If you have troubles post the errors in the Forum first and we can check how to fix them.

To get the program running you have to first configure the example with CMake (the sourcecode path is the folder where the CMakeLists.txt lies, the build path is the source path and "/build". Afterwards create a project file with CMake for your IDE (most of you) or a "make" configuration (nerdy way) and try to compile and run the program afterwards. You should see a colored cube with a black background.

----

Tasks:

Your main task will be to understand the sourcecode and get the project running on your desktop/laptop. Please use for this the links in the ressources. We stronly suggest to read the learnopengl.com tutorials number 1 (OpenGL) - 5 (Shaders) for this.

To prove that you understood the code you will have to find the position in the source code where the background color is set and then change the color according to the first 6 digits or your legi number (e.g. 11-789-5XX). You can use pairs of two digits to express one color channel but be aware that you have to rescale the values. Create a screenshot from your result and upload it to OLAT.

----

Learning targets:

The coding part in this exercise is small becaue we want you to spend the time in checking the different parts of this program and read the above mentioned tutorials. To prepare for the rest of the course you should have understood:

...that GLFW is the windowing library of this program and it does a lot of magic for you

...that GLEW is a wrapper libary to load OpenGL extensions (we use this instead of glad which is often used in the tutorials)

...where the sourcecode in a shader is defined and how it is loaded

...where the information of the cube is defined

...where the "render loop" is running

...where the drawing of the cube in the "render loop" is happening.

...how you change the background color in an OpenGL app.

----

Documentation & resources:

- [GLFW Documentation](http://www.glfw.org/docs/latest/index.html)
- [Glad Documentation on GitHub](https://github.com/Dav1dde/glad)
- [OpenGL - Getting started - FAQ](https://www.khronos.org/opengl/wiki/Getting_Started)
- [OpenGL-tutorial.org](http://www.opengl-tutorial.org)
- [Learn OpenGL tutorials [learnopengl.com]](https://learnopengl.com)
 

----
About OpenGL

It is important to notice that OpenGL is defined as a programming interface and not as a software library. This means that OpenGL just provides a set of functions and values definitions that should be implemented by third parties, like hardware companies or operating system developers. In modern desktop systems, the OpenGL implementation is tipically provided with the graphics card drivers.

From version 3.0 of OpenGL, a large reorganization of the API took place to represent in a better way the architecture of modern GPUs. Large parts of the original API has been marked as deprecated and several API implementations do not support them anymore (most notably Mac OS X). Two API profiles now exist within OpenGL: Core profile which only supports the modern API, and Compatibility profile which still allows the use of deprecated API calls and its main purpose is to run legacy code in modern GPUs.

Another important remark about OpenGL is that it only defines the interface to handle rendering commands and to manage the render data lifecycle within a properly initialized OpenGL environment (usually called "context"). However, this context is highly dependent on the operating system capabilities and access control mechanisms, and thus the creation of the context itself is not defined in the OpenGL API and must be done using some platform dependent library. Moreover, OpenGL only deals with the rendering part and it does not provide any functionality to receive user interface events as mouse movements or keyboard movements.

Fortunately, several libraries exist to handle this shortcomings, simplify the context creation and provide additional functionality to get the events generated by the user in the rendering window. GLUT and GLFW, for example, are two widely used cross-platform libraries dealing with those issues. [GLUT](https://www.opengl.org/resources/libraries/glut/) (and its open-source clone [FreeGLUT](http://freeglut.sourceforge.net)) development stopped long time ago and nowadays is deprecated. GLFW is very similar to GLUT but provides some additional features is still actively maintained.

You can use whatever development environment suits you best: a full IDE as Visual Studio, Xcode or Qt Creator, a powerful text editor as SublimeText together with a building tool as CMake and a command line compiler, etc.

----
 
Addendum:

An OpenGL loader library is a library to load pointers to OpenGL core functions and extensions. Core OpenGL functions should be accessible using the proper system headers and linking options and thus these libraries are only required to access extensions. However, they are often used to simplify the cross-platform compilation of OpenGL apps. Some examples of loading libraries are [GLEW](http://glew.sourceforge.net), which is the one we use here and [Glad](https://github.com/Dav1dde/glad) which follows a simpler approach, generating the code for the loader as an additional source file to be included in the project. Check the websites for additional explanations in case you have troubles.

 