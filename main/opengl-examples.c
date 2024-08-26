#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "opengl-examples.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void opengl_shader_program_create(opengl_ctx_t* ctx, opengl_scene_type_t type) {
	int  success;
	char info[512];
	const char* vertex_shader_source;
	const char* frag_shader_source;

	if (type == TYPE_TRIANGLE_01 || type == TYPE_RECTANGLE_01) {
		vertex_shader_source =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;					\
			 void main() {											\
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
			 }														\
			";
		frag_shader_source =
			"#version 330 core\n"
			"out vec4 FragColor;							\
			 void main() {									\
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);	\
			 }												\
			";
	}
	if (type == TYPE_TRIANGLE_02 || type == TYPE_RECTANGLE_02) {
		vertex_shader_source = 
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;					\
			 layout (location = 1) in vec3 aColor;					\
			 out vec3 outColor;                                     \
			 void main() {											\
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
				outColor = aColor;                                  \
			 }														\
			";
		frag_shader_source =
			"#version 330 core\n"
			"out vec4 FragColor;							\
			 in vec3 outColor;                              \
			 void main() {									\
				FragColor = vec4(outColor, 1.0);   			\
			 }												\
			";
	}
	if (type == TYPE_TEXTURE_01) {
		vertex_shader_source =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;					\
			 layout (location = 1) in vec2 aTexCoord;				\
			 out vec2 TexCoord;										\
			 void main() {											\
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
				TexCoord = aTexCoord;								\
			 }														\
			";
		//注意这里的texture0是一个uniform的全局变量，但是我们没有设置这个值。
		frag_shader_source =
			"#version 330 core\n"
			"out vec4 FragColor;							\
			 in vec2 TexCoord;								\
			 uniform sampler2D texture0;					\
			 void main() {									\
				FragColor = texture(texture0, TexCoord);	\
			 }												\
			";
	}
	if (type == TYPE_TEXTURE_02) {
		vertex_shader_source =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;					\
			 layout (location = 1) in vec2 aTexCoord;				\
			 out vec2 TexCoord;										\
			 void main() {											\
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
				TexCoord = aTexCoord;								\
			 }														\
			";
		
		frag_shader_source =
			"#version 330 core\n"
			"out vec4 FragColor;																\
			 in vec2 TexCoord;																	\
			 uniform sampler2D texture0;														\
			 uniform sampler2D texture1;														\
			 void main() {																		\
				FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);	\
			 }																					\
			";
	}
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, sizeof(info), NULL, info);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", info);
	}
	unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &frag_shader_source, NULL);
	glCompileShader(frag_shader);
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(frag_shader, sizeof(info), NULL, info);
		printf("ERROR::SHADER::FRAG::COMPILATION_FAILED: %s\n", info);
	}
	ctx->shader_program = glCreateProgram();
	glAttachShader(ctx->shader_program, vertex_shader);
	glAttachShader(ctx->shader_program, frag_shader);
	glLinkProgram(ctx->shader_program);

	glGetProgramiv(ctx->shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ctx->shader_program, sizeof(info), NULL, info);
		printf("ERROR::SHADER::LINK_FAILED: %s\n", info);
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);
}

void opengl_shader_program_use(opengl_ctx_t* ctx) {
	glUseProgram(ctx->shader_program);
}

void opengl_shader_program_destroy(opengl_ctx_t* ctx) {
	glDeleteProgram(ctx->shader_program);
}

void opengl_scene_create(opengl_ctx_t* ctx, opengl_scene_type_t type) {
	float vertices[64] = {0};	//最多16顶点属性，每个属性一个vec4，所以这里设置最多64个值
	//画矩形时候使用。
	unsigned int indices[] = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	if (type == TYPE_TRIANGLE_01) {
		float v[9] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		memcpy(vertices, v, sizeof(v));
	}
	if (type == TYPE_TRIANGLE_02) {
		float v[18] = {
			// 位置              // 颜色
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
			0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
		};
		memcpy(vertices, v, sizeof(v));
	}
	if (type == TYPE_RECTANGLE_01) {
		float v[12] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
		   -0.5f, -0.5f, 0.0f,  // bottom left
		   -0.5f,  0.5f, 0.0f   // top left 
		};
		memcpy(vertices, v, sizeof(v));
	}
	if (type == TYPE_RECTANGLE_02) {
		float v[24] = {
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,	// 右上
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // 右下
		   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // 左下
		   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // 左上
		};
		memcpy(vertices, v, sizeof(v));
	}
	if (type == TYPE_TEXTURE_01) {
		float v[15] = {
		   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // 左下角
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // 右下角
			0.0f,  0.5f, 0.0f,  0.5f, 1.0f, // 上中
		};
		memcpy(vertices, v, sizeof(v));
	}
	if (type == TYPE_TEXTURE_02) {
		float v[20] = {
			0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   // 右上
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // 右下
		   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // 左下
		   -0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // 左上
		};
		memcpy(vertices, v, sizeof(v));
	}
	// 0. 创建和绑定VAO
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);
	// 1. 复制顶点数组到缓冲中供OpenGL使用
	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	if (type == TYPE_RECTANGLE_01 || type == TYPE_RECTANGLE_02 || type == TYPE_TEXTURE_02) {
		// 2. 复制索引数据到元素缓冲中
		glGenBuffers(1, &ctx->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	// 3. 设置顶点属性指针
	if (type == TYPE_TRIANGLE_01 || type == TYPE_RECTANGLE_01) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	if (type == TYPE_TRIANGLE_02 || type == TYPE_RECTANGLE_02) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	if (type == TYPE_TEXTURE_01 || type == TYPE_TEXTURE_02) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	if (type == TYPE_TEXTURE_01) {
		int width, height, nrChannels;
		unsigned char* data = stbi_load("../../../resource/wall.jpg", &width, &height, &nrChannels, 0);
		
		glGenTextures(1, &ctx->textures[0]);
		glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);

		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);//可选，防止意外修改
		stbi_image_free(data);
	}
	if (type == TYPE_TEXTURE_02) {
		int width, height, nrChannels;
		unsigned char* data = stbi_load("../../../resource/container.jpg", &width, &height, &nrChannels, 0);

		glGenTextures(1, &ctx->textures[0]);
		glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);

		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);//可选，防止意外修改
		stbi_image_free(data);

		data = stbi_load("../../../resource/awesomeface.png", &width, &height, &nrChannels, 0);

		glGenTextures(1, &ctx->textures[1]);
		glBindTexture(GL_TEXTURE_2D, ctx->textures[1]);

		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);//可选，防止意外修改
		stbi_image_free(data);
		//和着色器中的片段着色器里的纹理采样器对应,并且对着色器配置前需要先use
		opengl_shader_program_use(ctx);
		glUniform1i(glGetUniformLocation(ctx->shader_program, "texture0"), 0);
		glUniform1i(glGetUniformLocation(ctx->shader_program, "texture1"), 1);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

void opengl_scene_draw(opengl_ctx_t* ctx, opengl_scene_type_t type) {
	glBindVertexArray(ctx->vao);
	if (type == TYPE_TEXTURE_01) {
		glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
	}
	if (type == TYPE_TEXTURE_02) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, ctx->textures[1]);
	}
	if (type == TYPE_TRIANGLE_01 || type == TYPE_TRIANGLE_02 || type == TYPE_TEXTURE_01) {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	if (type == TYPE_RECTANGLE_01 || type == TYPE_RECTANGLE_02 || type == TYPE_TEXTURE_02) {
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //索引是6个
	}
}

void opengl_scene_destroy(opengl_ctx_t* ctx, opengl_scene_type_t type) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);

	if (type == TYPE_RECTANGLE_01) {
		glDeleteBuffers(1, &ctx->ebo);
	}
	if (type == TYPE_TEXTURE_01) {
		glDeleteTextures(1, &ctx->textures[0]);
	}
}