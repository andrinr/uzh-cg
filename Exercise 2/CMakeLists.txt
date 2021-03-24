cmake_minimum_required(VERSION 3.2)

project(glexample2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_DIRNAME "CMake" CACHE INTERNAL "Generic name of the folder with CMake modules")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/${CMAKE_DIRNAME})

#message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message(STATUS "\n######## Computer graphics exercise 1 ########")
message(STATUS "\nPlease specify above the path where you moved the GLFW binaries.")
message(STATUS "\nFor users of a visual studio compiler GLFW comes with this zip file.")
message(STATUS "\n################")

# set fix paths to variables
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")
set(BINARY_DIR "${CMAKE_SOURCE_DIR}/external")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# for visual studio user glfw comes prebuild with the package
if(MSVC)
  set(GLFW_ROOT "${EXTERNAL_DIR}/glfw")
else()
  set(GLFW_ROOT CACHE STRING "GLFW Root directory..")
endif()

# set these paths
set(CMAKE_PREFIX_PATH "${EXTERNAL_DIR}/glew")
set(CMAKE_LIBRARY_PATH "${EXTERNAL_DIR}/glew/lib-win/msvc14/")

# find OpenGL and GLFW in system
find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)

# set external dependencies
set(ext_includes
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${EXTERNAL_DIR}
)

# add all sources in source folder for viewer project 
set(sources  
  ${SRC_DIR}/GLApp.h 
  ${SRC_DIR}/GLApp.cpp
  ${SRC_DIR}/GLExample.h
  ${SRC_DIR}/GLExample.cpp  
  ${SRC_DIR}/GLApp.cpp  
  ${SRC_DIR}/GLIncludes.h 
  ${SRC_DIR}/Shape.h
  ${SRC_DIR}/Shape.cpp
  ${SRC_DIR}/Cube.h
  ${SRC_DIR}/Cube.cpp
  ${SRC_DIR}/Cuboid.h
  ${SRC_DIR}/Cuboid.cpp
  ${SRC_DIR}/main.cpp
)

# set up IDE projects and set dependencies
add_executable(${PROJECT_NAME} ${ext_sources} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC 
                           ${ext_includes} 
                           ${OPENGL_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} GLEW::GLEW)

# copy libs to FOLDER
if(MSVC)
  file(COPY ${EXTERNAL_DIR}/glew/lib-win/msvc14/glew32.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug/)
  file(COPY ${EXTERNAL_DIR}/glew/lib-win/msvc14/glew32.dll DESTINATION ${CMAKE_BINARY_DIR}/Release/)
endif()
