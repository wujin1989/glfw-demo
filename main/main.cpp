#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <chrono>
#include <thread>
#include "opengl-examples.h"

#define SCENE	TYPE_CAMERA_02
opengl_ctx_t opengl_ctx;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	printf("window size changed, width: %d, height: %d\n", width, height);

	opengl_ctx.viewport_width = width;
	opengl_ctx.viewport_height = height;
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	static bool fisrt = true;
	static float last_x;
	static float last_y;

	float x = (float)xpos;
	float y = (float)ypos;

	if (fisrt){
		last_x = x;
		last_y = y;
		fisrt = false;
	}
	float xoffset = x - last_x;
	float yoffset = last_y - y;

	last_x = x;
	last_y = y;

	opengl_camera_rotate(&opengl_ctx.camera, xoffset, yoffset);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	opengl_camera_zoom(&opengl_ctx.camera, (float)yoffset);
}


static void process_input(opengl_ctx_t* ctx, GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		opengl_camera_move(&ctx->camera, FORWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		opengl_camera_move(&ctx->camera, BACKWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		opengl_camera_move(&ctx->camera, LEFT);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		opengl_camera_move(&ctx->camera, RIGHT);
	}
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

	opengl_camera_init(&opengl_ctx.camera, 
		glm::vec3(0.0f, 0.0f, 3.0f), 
		0.0f, 
		-90.0f, //因为要保证Z轴正方向朝向屏幕外，所以需要保证X轴和Z轴之间是90度。
		(float)(opengl_ctx.viewport_width / opengl_ctx.viewport_height));

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "GLFW-Demo", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		abort();
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		abort();
	}
	opengl_shader_program_create(&opengl_ctx, SCENE);
	opengl_scene_create(&opengl_ctx, SCENE);
	opengl_shader_program_use(&opengl_ctx);

	while (!glfwWindowShouldClose(window)) {
		process_input(&opengl_ctx, window);
		
		opengl_scene_draw(&opengl_ctx, SCENE);

		glfwPollEvents();
		glfwSwapBuffers(window);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
	opengl_scene_destroy(&opengl_ctx);
	opengl_shader_program_destroy(&opengl_ctx);

	glfwTerminate();
	return 0;
}