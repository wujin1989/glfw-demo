#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <chrono>
#include <thread>
#include "opengl-examples.h"

#define SCENE	TYPE_CAMERA_01
opengl_ctx_t opengl_ctx;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	printf("window size changed, width: %d, height: %d\n", width, height);

	opengl_ctx.viewport_width = width;
	opengl_ctx.viewport_height = height;
}

static void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

int main(void) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	unsigned int window_width = 800;
	unsigned int window_height = 600;

	opengl_ctx.viewport_width = window_width;
	opengl_ctx.viewport_height = window_height;

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "GLFW-Demo", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		abort();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		abort();
	}
	opengl_shader_program_create(&opengl_ctx, SCENE);
	opengl_scene_create(&opengl_ctx, SCENE);
	opengl_shader_program_use(&opengl_ctx);

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		opengl_scene_draw(&opengl_ctx, SCENE);

		glfwPollEvents();
		glfwSwapBuffers(window);
		//std::this_thread::sleep_for(std::chrono::milliseconds(40));
	}
	opengl_scene_destroy(&opengl_ctx, SCENE);
	opengl_shader_program_destroy(&opengl_ctx);

	glfwTerminate();
	return 0;
}