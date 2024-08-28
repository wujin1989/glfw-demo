#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include "opengl-examples.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

static void _common_shader_program_create(opengl_ctx_t* ctx, const char* vertex_shader_source, const char* frag_shader_source) {
	int  success;
	char info[512];

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

static void _triangle01_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;					\
		 void main() {											\
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
		 }														\
		";
	const char* frag_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;							\
		 void main() {									\
			FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);	\
		 }												\
		";
	_common_shader_program_create(ctx, vertex_shader_source, frag_shader_source);
}

static void _triangle02_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;					\
		 layout (location = 1) in vec3 aColor;					\
		 out vec3 outColor;                                     \
		 void main() {											\
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
			outColor = aColor;                                  \
		 }														\
		";
	const char* frag_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;							\
		 in vec3 outColor;                              \
		 void main() {									\
			FragColor = vec4(outColor, 1.0);   			\
		 }												\
		";
	_common_shader_program_create(ctx, vertex_shader_source, frag_shader_source);
}

static void _rectangle01_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;					\
		 void main() {											\
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
		 }														\
		";
	const char* frag_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;							\
		 void main() {									\
			FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);	\
		 }												\
		";
	_common_shader_program_create(ctx, vertex_shader_source, frag_shader_source);
}

static void _rectangle02_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;					\
		 layout (location = 1) in vec3 aColor;					\
		 out vec3 outColor;                                     \
		 void main() {											\
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
			outColor = aColor;                                  \
		 }														\
		";
	const char* frag_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;							\
		 in vec3 outColor;                              \
		 void main() {									\
			FragColor = vec4(outColor, 1.0);   			\
		 }												\
		";
	_common_shader_program_create(ctx, vertex_shader_source, frag_shader_source);
}

static void _texture01_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
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
	const char* frag_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;							\
		 in vec2 TexCoord;								\
		 uniform sampler2D texture0;					\
		 void main() {									\
			FragColor = texture(texture0, TexCoord);	\
		 }												\
		";
	_common_shader_program_create(ctx, vertex_shader_source, frag_shader_source);
}

static void _texture02_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;					\
		 layout (location = 1) in vec2 aTexCoord;				\
		 out vec2 TexCoord;										\
		 void main() {											\
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
			TexCoord = aTexCoord;								\
		 }														\
		";
	const char* frag_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;																\
		 in vec2 TexCoord;																	\
		 uniform sampler2D texture0;														\
		 uniform sampler2D texture1;														\
		 void main() {																		\
			FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);	\
		 }																					\
		";
	_common_shader_program_create(ctx, vertex_shader_source, frag_shader_source);
}

static void _matrix01_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;					\
		 layout (location = 1) in vec2 aTexCoord;				\
		 out vec2 TexCoord;										\
		 uniform mat4 uTransform;								\
		 void main() {											\
			gl_Position = uTransform * vec4(aPos, 1.0);			\
			TexCoord = aTexCoord;								\
		 }														\
		";

	const char* frag_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;																\
		 in vec2 TexCoord;																	\
		 uniform sampler2D texture0;														\
		 uniform sampler2D texture1;														\
		 void main() {																		\
			FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);	\
		 }																					\
		";
	_common_shader_program_create(ctx, vertex_shader_source, frag_shader_source);
}

static void _matrix02_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;					\
		 layout (location = 1) in vec2 aTexCoord;				\
		 out vec2 TexCoord;										\
		 uniform mat4 uTransform;								\
		 void main() {											\
			gl_Position = uTransform * vec4(aPos, 1.0);			\
			TexCoord = aTexCoord;								\
		 }														\
		";

	const char* frag_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;																\
		 in vec2 TexCoord;																	\
		 uniform sampler2D texture0;														\
		 uniform sampler2D texture1;														\
		 void main() {																		\
			FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);	\
		 }																					\
		";
	_common_shader_program_create(ctx, vertex_shader_source, frag_shader_source);
}

static void _triangle01_scene_create(opengl_ctx_t* ctx) {
	float vertices[] = {
		-0.5f,	-0.5f,	0.0f,
		0.5f,	-0.5f,	0.0f,
		0.0f,	0.5f,	0.0f
	};
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);

	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，解绑VBO, 防止意外修改
	glBindVertexArray(0);//可选，解绑VAO, 防止意外修改
}

static void _triangle02_scene_create(opengl_ctx_t* ctx) {
	float vertices[] = {
				// 位置					// 颜色
		0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	0.0f,   // 右下
		-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,   // 左下
		0.0f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f    // 顶部
	};
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);

	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

static void _rectangle01_scene_create(opengl_ctx_t* ctx) {
	float vertices[] = {
		0.5f,	0.5f,	0.0f,
		0.5f,	-0.5f,	0.0f,
		-0.5f,	-0.5f,	0.0f,
		-0.5f,	0.5f,	0.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	// 0. 创建和绑定VAO
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);
	// 1. 复制顶点数组到缓冲中供OpenGL使用
	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 2. 复制索引数据到元素缓冲中
	glGenBuffers(1, &ctx->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 3. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

static void _rectangle02_scene_create(opengl_ctx_t* ctx) {
	float vertices[] = {
		0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	0.0f,	// 右上
		0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,  // 右下
		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,  // 左下
		-0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	0.0f,  // 左上
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);

	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ctx->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

static void _texture01_scene_create(opengl_ctx_t* ctx) {
	float vertices[] = {
		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f, // 左下角
		0.5f,	-0.5f,	0.0f,	1.0f,	0.0f, // 右下角
		0.0f,	0.5f,	0.0f,	0.5f,	1.0f, // 上中
	};
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);

	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//加载纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load("../../../resource/wall.jpg", &width, &height, &nrChannels, 0);

	glGenTextures(1, &ctx->textures[0]);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);//可选，防止意外修改
	stbi_image_free(data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

static void _texture02_scene_create(opengl_ctx_t* ctx) {
	float vertices[] = {
		0.5f,	0.5f,	0.0f,	1.0f,	1.0f,   // 右上
		0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,   // 右下
		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,   // 左下
		-0.5f,	0.5f,	0.0f,	0.0f,	1.0f    // 左上
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);

	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ctx->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	////////////////////////////////////////////////////////////////////////////
	//加载的图片的(0,0)在左上角，但是opengl的视口的原点(0,0)在左下角
	stbi_set_flip_vertically_on_load(1);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("../../../resource/container.jpg", &width, &height, &nrChannels, 0);

	glGenTextures(1, &ctx->textures[0]);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);

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
	//把纹理单元赋值给采样器
	glUniform1i(glGetUniformLocation(ctx->shader_program, "texture0"), 0);
	glUniform1i(glGetUniformLocation(ctx->shader_program, "texture1"), 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

static void _matrix01_scene_create(opengl_ctx_t* ctx) {
	float vertices[] = {
		0.5f,	0.5f,	0.0f,	1.0f,	1.0f,   // 右上
		0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,   // 右下
		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,   // 左下
		-0.5f,	0.5f,	0.0f,	0.0f,	1.0f    // 左上
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);

	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ctx->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	////////////////////////////////////////////////////////////////////////////
	//加载的图片的(0,0)在左上角，但是opengl的视口的原点(0,0)在左下角
	stbi_set_flip_vertically_on_load(1);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("../../../resource/container.jpg", &width, &height, &nrChannels, 0);

	glGenTextures(1, &ctx->textures[0]);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);

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
	//把纹理单元赋值给采样器
	glUniform1i(glGetUniformLocation(ctx->shader_program, "texture0"), 0);
	glUniform1i(glGetUniformLocation(ctx->shader_program, "texture1"), 1);

	glm::mat4 trans = glm::mat4(1.0f);	//生成一个单位矩阵
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uTransform"), 1, GL_FALSE, glm::value_ptr(trans));

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

static void _matrix02_scene_create(opengl_ctx_t* ctx) {
	float vertices[] = {
		0.5f,	0.5f,	0.0f,	1.0f,	1.0f,   // 右上
		0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,   // 右下
		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,   // 左下
		-0.5f,	0.5f,	0.0f,	0.0f,	1.0f    // 左上
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	glGenVertexArrays(1, &ctx->vao);
	glBindVertexArray(ctx->vao);

	glGenBuffers(1, &ctx->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ctx->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	////////////////////////////////////////////////////////////////////////////
	//加载的图片的(0,0)在左上角，但是opengl的视口的原点(0,0)在左下角
	stbi_set_flip_vertically_on_load(1);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("../../../resource/container.jpg", &width, &height, &nrChannels, 0);

	glGenTextures(1, &ctx->textures[0]);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);

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
	//把纹理单元赋值给采样器
	glUniform1i(glGetUniformLocation(ctx->shader_program, "texture0"), 0);
	glUniform1i(glGetUniformLocation(ctx->shader_program, "texture1"), 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

static void _triangle01_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

static void _triangle02_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

static void _rectangle01_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //索引是6个
}

static void _rectangle02_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

static void _texture01_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

static void _texture02_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[1]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

static void _matrix01_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[1]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

static void _matrix02_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	//确保调用下面之前已经调用了glUseProgram
	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uTransform"), 1, GL_FALSE, glm::value_ptr(trans));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[1]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

static void _triangle01_scene_destroy(opengl_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);
}

static void _triangle02_scene_destroy(opengl_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);
}

static void _rectangle01_scene_destroy(opengl_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);
	glDeleteBuffers(1, &ctx->ebo);
}

static void _rectangle02_scene_destroy(opengl_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);
	glDeleteBuffers(1, &ctx->ebo);
}

static void _texture01_scene_destroy(opengl_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);
	glDeleteTextures(1, &ctx->textures[0]);
}

static void _texture02_scene_destroy(opengl_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);
	glDeleteBuffers(1, &ctx->ebo);
	glDeleteTextures(1, &ctx->textures[0]);
	glDeleteTextures(1, &ctx->textures[1]);
}

static void _matrix01_scene_destroy(opengl_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);
	glDeleteBuffers(1, &ctx->ebo);
	glDeleteTextures(1, &ctx->textures[0]);
	glDeleteTextures(1, &ctx->textures[1]);
}

static void _matrix02_scene_destroy(opengl_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);
	glDeleteBuffers(1, &ctx->ebo);
	glDeleteTextures(1, &ctx->textures[0]);
	glDeleteTextures(1, &ctx->textures[1]);
}

void opengl_shader_program_create(opengl_ctx_t* ctx, opengl_scene_type_t type) {
	if (type == TYPE_TRIANGLE_01) {
		_triangle01_shader_program_create(ctx);
	}
	if (type == TYPE_TRIANGLE_02) {
		_triangle02_shader_program_create(ctx);
	}
	if (type == TYPE_RECTANGLE_01) {
		_rectangle01_shader_program_create(ctx);
	}
	if (type == TYPE_RECTANGLE_02) {
		_rectangle02_shader_program_create(ctx);
	}
	if (type == TYPE_TEXTURE_01) {
		_texture01_shader_program_create(ctx);
	}
	if (type == TYPE_TEXTURE_02) {
		_texture02_shader_program_create(ctx);
	}
	if (type == TYPE_MATRIX_01) {
		_matrix01_shader_program_create(ctx);
	}
	if (type == TYPE_MATRIX_02) {
		_matrix02_shader_program_create(ctx);
	}
}

void opengl_shader_program_use(opengl_ctx_t* ctx) {
	glUseProgram(ctx->shader_program);
}

void opengl_shader_program_destroy(opengl_ctx_t* ctx) {
	glDeleteProgram(ctx->shader_program);
}

void opengl_scene_create(opengl_ctx_t* ctx, opengl_scene_type_t type) {
	if (type == TYPE_TRIANGLE_01) {
		_triangle01_scene_create(ctx);
	}
	if (type == TYPE_TRIANGLE_02) {
		_triangle02_scene_create(ctx);
	}
	if (type == TYPE_RECTANGLE_01) {
		_rectangle01_scene_create(ctx);
	}
	if (type == TYPE_RECTANGLE_02) {
		_rectangle02_scene_create(ctx);
	}
	if (type == TYPE_TEXTURE_01) {
		_texture01_scene_create(ctx);
	}
	if (type == TYPE_TEXTURE_02) {
		_texture02_scene_create(ctx);
	}
	if (type == TYPE_MATRIX_01) {
		_matrix01_scene_create(ctx);
	}
	if (type == TYPE_MATRIX_02) {
		_matrix02_scene_create(ctx);
	}
}

void opengl_scene_draw(opengl_ctx_t* ctx, opengl_scene_type_t type) {
	if (type == TYPE_TRIANGLE_01) {
		_triangle01_scene_draw(ctx);
	}
	if (type == TYPE_TRIANGLE_02) {
		_triangle02_scene_draw(ctx);
	}
	if (type == TYPE_RECTANGLE_01) {
		_rectangle01_scene_draw(ctx);
	}
	if (type == TYPE_RECTANGLE_02) {
		_rectangle02_scene_draw(ctx);
	}
	if (type == TYPE_TEXTURE_01) {
		_texture01_scene_draw(ctx);
	}
	if (type == TYPE_TEXTURE_02) {
		_texture02_scene_draw(ctx);
	}
	if (type == TYPE_MATRIX_01) {
		_matrix01_scene_draw(ctx);
	}
	if (type == TYPE_MATRIX_02) {
		_matrix02_scene_draw(ctx);
	}
}

void opengl_scene_destroy(opengl_ctx_t* ctx, opengl_scene_type_t type) {
	if (type == TYPE_TRIANGLE_01) {
		_triangle01_scene_destroy(ctx);
	}
	if (type == TYPE_TRIANGLE_02) {
		_triangle02_scene_destroy(ctx);
	}
	if (type == TYPE_RECTANGLE_01) {
		_rectangle01_scene_destroy(ctx);
	}
	if (type == TYPE_RECTANGLE_02) {
		_rectangle02_scene_destroy(ctx);
	}
	if (type == TYPE_TEXTURE_01) {
		_texture01_scene_destroy(ctx);
	}
	if (type == TYPE_TEXTURE_02) {
		_texture02_scene_destroy(ctx);
	}
	if (type == TYPE_MATRIX_01) {
		_matrix01_scene_destroy(ctx);
	}
	if (type == TYPE_MATRIX_02) {
		_matrix02_scene_destroy(ctx);
	}
}