#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "triangle.h"

void triangle_create(triangle_ctx_t* ctx) {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	// 0. �����Ͱ�VAO
	glGenVertexArrays(1, &ctx->VAO);
	glBindVertexArray(ctx->VAO);

	// 1. ���ƶ������鵽�����й�OpenGLʹ��
	glGenBuffers(1, &ctx->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 2. ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//��һ�������ϸ��Ҫ�ģ���ͨ���������������Ա��������޸�VBO��
	// һ������󶨣��κζ�GL_ARRAY_BUFFER�ĺ�������������Ӱ�쵱ǰ��VBO��
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//�� VAO ���ڻ״̬ʱ������ȡ���� EBO����Ϊ�󶨵�Ԫ�ػ���������洢�� VAO �У����� EBO �󶨡�
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//��һ���ǿ�ѡ�ģ���ͨ���������������Ա�����֮��Ĳ����������޸ĵ�ǰVAO��
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
	// 3. ��������Ⱦһ������ʱҪʹ����ɫ������
	glUseProgram(ctx->shaderProgram);

	glBindVertexArray(ctx->VAO);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//�߿�ģʽ�� glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)�� Ĭ�����ģʽ
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void triangle_destroy(triangle_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->VAO);
	glDeleteBuffers(1, &ctx->VBO);
	glDeleteProgram(ctx->shaderProgram);
}