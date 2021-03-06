cmake_minimum_required(VERSION 3.6)
project(opengl_template VERSION 1.0)

#set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
#set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -flto -ftree-vectorize -march=native -O3 -mtune=generic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra")
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB SOURCES "src/Shader/*.cpp" "src/Application/*.cpp" "src/imgui/*.cpp" )

add_executable(opengl_template src/main.cpp src/glew.c ${SOURCES})

target_link_libraries(opengl_template ${OPENGL_gl_LIBRARY} glfw3 GL)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) 