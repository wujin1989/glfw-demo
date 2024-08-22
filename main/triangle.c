#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "triangle.h"

void triangle_create(triangle_ctx_t* ctx) {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	// 0. 创建和绑定VAO
	glGenVertexArrays(1, &ctx->VAO);
	glBindVertexArray(ctx->VAO);

	// 1. 复制顶点数组到缓冲中供OpenGL使用
	glGenBuffers(1, &ctx->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 2. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//这一步不是严格必要的，但通常建议这样做，以避免意外修改VBO。
	// 一旦解除绑定，任何对GL_ARRAY_BUFFER的后续操作都不会影响当前的VBO。
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//当 VAO 处于活动状态时，请勿取消绑定 EBO，因为绑定的元素缓冲区对象存储在 VAO 中；保持 EBO 绑定。
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//这一步是可选的，但通常建议这样做，以避免在之后的操作中意外修改当前VAO。
	glBindVertexArray(0);

	const char* VERTEX_SHADER_SOURCE =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;					\
		 void main() {											\
			 gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
		 }														\
	    ";
	ctx->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ctx->vertexShader, 1, &VERTEX_SHADER_SOURCE, NULL);
	glCompileShader(ctx->vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(ctx->vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ctx->vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog);
	}
	const char* FRAG_SHADER_SOURCE =
		"#version 330 core\n"
		"out vec4 FragColor;							\
		 void main() {									\
			 FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);	\
		 }												\
	    ";
	ctx->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ctx->fragmentShader, 1, &FRAG_SHADER_SOURCE, NULL);
	glCompileShader(ctx->fragmentShader);

	glGetShaderiv(ctx->fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ctx->fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAG::COMPILATION_FAILED: %s\n", infoLog);
	}
	ctx->shaderProgram = glCreateProgram();
	glAttachShader(ctx->shaderProgram, ctx->vertexShader);
	glAttachShader(ctx->shaderProgram, ctx->fragmentShader);
	glLinkProgram(ctx->shaderProgram);

	glGetProgramiv(ctx->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ctx->shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::LINK_FAILED: %s\n", infoLog);
	}
	glDeleteShader(ctx->vertexShader);
	glDeleteShader(ctx->fragmentShader);
}

void triangle_draw(triangle_ctx_t* ctx) {
	// 3. 当我们渲染一个物体时要使用着色器程序
	glUseProgram(ctx->shaderProgram);

	glBindVertexArray(ctx->VAO);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//线框模式， glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)： 默认填充模式
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void triangle_destroy(triangle_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->VAO);
	glDeleteBuffers(1, &ctx->VBO);
	glDeleteProgram(ctx->shaderProgram);
}