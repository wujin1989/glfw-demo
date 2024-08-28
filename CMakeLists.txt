cmake_minimum_required(VERSION 3.16)

project(glfw-demo)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)

include_directories(glad/include)
include_directories(third-party/glfw/include)
include_directories(third-party/stb)
include_directories(third-party/glm)

link_directories(third-party/glfw/lib)

set(SRCS
	main/main.cpp
	main/opengl-examples.cpp
	main/vulkan-examples.cpp
	glad/src/glad.c
)

add_executable(glfw-demo ${SRCS})
target_link_libraries(glfw-demo PUBLIC glfw3)