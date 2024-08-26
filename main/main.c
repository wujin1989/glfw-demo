#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include "opengl-examples.h"

opengl_ctx_t opengl_ctx;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	printf("window size changed, width: %d, height: %d\n", width, height);
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
#if defined(__APPLE__)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW-Demo", NULL, NULL);
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
	opengl_shader_program_create(&opengl_ctx, TYPE_TEXTURE_02);
	opengl_scene_create(&opengl_ctx, TYPE_TEXTURE_02);
	opengl_shader_program_use(&opengl_ctx);

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		opengl_scene_draw(&opengl_ctx, TYPE_TEXTURE_02);

		glfwPollEvents();
		glfwSwapBuffers(window);
		thrd_sleep(&(struct timespec) { .tv_sec = 0, .tv_nsec = 40000000 }, NULL);
	}
	opengl_scene_destroy(&opengl_ctx, TYPE_TEXTURE_02);
	opengl_shader_program_destroy(&opengl_ctx);

	glfwTerminate();
	return 0;
}