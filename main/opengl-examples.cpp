#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include "opengl-examples.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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

static void _coords01_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;										\
		 layout (location = 1) in vec2 aTexCoord;									\
		 out vec2 TexCoord;															\
		 uniform mat4 uModel;														\
		 uniform mat4 uView;														\
		 uniform mat4 uProjection;													\
		 void main() {																\
			gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);			\
			TexCoord = aTexCoord;													\
		 }																			\
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

static void _coords02_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;										\
		 layout (location = 1) in vec2 aTexCoord;									\
		 out vec2 TexCoord;															\
		 uniform mat4 uModel;														\
		 uniform mat4 uView;														\
		 uniform mat4 uProjection;													\
		 void main() {																\
			gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);			\
			TexCoord = aTexCoord;													\
		 }																			\
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

static void _camera01_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;										\
		 layout (location = 1) in vec2 aTexCoord;									\
		 out vec2 TexCoord;															\
		 uniform mat4 uModel;														\
		 uniform mat4 uView;														\
		 uniform mat4 uProjection;													\
		 void main() {																\
			gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);			\
			TexCoord = aTexCoord;													\
		 }																			\
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

static void _camera02_shader_program_create(opengl_ctx_t* ctx) {
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;										\
		 layout (location = 1) in vec2 aTexCoord;									\
		 out vec2 TexCoord;															\
		 uniform mat4 uModel;														\
		 uniform mat4 uView;														\
		 uniform mat4 uProjection;													\
		 void main() {																\
			gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);			\
			TexCoord = aTexCoord;													\
		 }																			\
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

static void _coords01_scene_create(opengl_ctx_t* ctx) {
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

	glm::mat4 model = glm::mat4(1.0f);
	//glm::vec3(1.0f, 0.0f, 0.0f)表示一个方向。这是一个单位向量
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	// 场景在Z轴向负方向移动，说明摄像机在Z轴向正方向移动。
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)(ctx->viewport_width / ctx->viewport_height), 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uView"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

static void _coords02_scene_create(opengl_ctx_t* ctx) {
	//立方体每个面有六个顶点
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

	glm::mat4 view = glm::mat4(1.0f);
	// 场景在Z轴向负方向移动，说明摄像机在Z轴向正方向移动。（x,y,z轴都是）
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)(ctx->viewport_width / ctx->viewport_height), 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uView"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

static void _camera01_scene_create(opengl_ctx_t* ctx) {
	//立方体每个面有六个顶点
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)(ctx->viewport_width / ctx->viewport_height), 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindBuffer(GL_ARRAY_BUFFER, 0);//可选，防止意外修改
	glBindVertexArray(0);//可选，防止意外修改
}

static void _camera02_scene_create(opengl_ctx_t* ctx) {
	//立方体每个面有六个顶点
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

static void _coords01_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[1]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

static void _coords02_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[1]);

	// 每次渲染迭代之前清除深度缓冲
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	float factor = (float)glfwGetTime();

	for (unsigned int i = 0; i < 10; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i + 20.0f;
		model = glm::rotate(model, factor * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

static void _camera01_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[1]);

	// 每次渲染迭代之前清除深度缓冲
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	float factor = (float)glfwGetTime();
	float radius = 10.0f;
	float camX = sin(factor) * radius;
	float camZ = cos(factor) * radius;

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(glm::vec3(camX, 0.0f, camZ),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uView"), 1, GL_FALSE, glm::value_ptr(view));

	for (unsigned int i = 0; i < 10; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i + 20.0f;
		model = glm::rotate(model, factor * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

static void _camera02_scene_draw(opengl_ctx_t* ctx) {
	glBindVertexArray(ctx->vao);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ctx->textures[1]);

	// 每次渲染迭代之前清除深度缓冲
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	float factor = (float)glfwGetTime();

	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uView"), 1, GL_FALSE, glm::value_ptr(ctx->camera.view));
	glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uProjection"), 1, GL_FALSE, glm::value_ptr(ctx->camera.projection));
	
	for (unsigned int i = 0; i < 10; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i + 20.0f;
		model = glm::rotate(model, factor * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(glGetUniformLocation(ctx->shader_program, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
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
	if (type == TYPE_COORDS_01) {
		_coords01_shader_program_create(ctx);
	}
	if (type == TYPE_COORDS_02) {
		_coords02_shader_program_create(ctx);
	}
	if (type == TYPE_CAMERA_01) {
		_camera01_shader_program_create(ctx);
	}
	if (type == TYPE_CAMERA_02) {
		_camera02_shader_program_create(ctx);
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
	if (type == TYPE_COORDS_01) {
		_coords01_scene_create(ctx);
	}
	if (type == TYPE_COORDS_02) {
		_coords02_scene_create(ctx);
	}
	if (type == TYPE_CAMERA_01) {
		_camera01_scene_create(ctx);
	}
	if (type == TYPE_CAMERA_02) {
		_camera02_scene_create(ctx);
	}
}

void opengl_scene_draw(opengl_ctx_t* ctx, opengl_scene_type_t type) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

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
	if (type == TYPE_COORDS_01) {
		_coords01_scene_draw(ctx);
	}
	if (type == TYPE_COORDS_02) {
		_coords02_scene_draw(ctx);
	}
	if (type == TYPE_CAMERA_01) {
		_camera01_scene_draw(ctx);
	}
	if (type == TYPE_CAMERA_02) {
		_camera02_scene_draw(ctx);
	}
}

void opengl_scene_destroy(opengl_ctx_t* ctx) {
	glDeleteVertexArrays(1, &ctx->vao);
	glDeleteBuffers(1, &ctx->vbo);
	glDeleteBuffers(1, &ctx->ebo);
	glDeleteTextures(sizeof(ctx->textures) / sizeof(ctx->textures[0]), ctx->textures);
}

glm::mat4 mylookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
	glm::vec3 front = glm::normalize(target - position);
	glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
	glm::vec3 up = glm::normalize(glm::cross(right, front));

	glm::mat4 translation = glm::mat4(1.0f);
	translation[3][0] = -position.x;
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;

	glm::mat4 rotation = glm::mat4(1.0f);
	//在 glm 中，由于列主布局，我们以 mat[col][row] 的形式访问元素
	rotation[0][0] = right.x;
	rotation[1][0] = right.y;
	rotation[2][0] = right.z;
	rotation[0][1] = up.x;
	rotation[1][1] = up.y;
	rotation[2][1] = up.z;
	rotation[0][2] = -front.x;
	rotation[1][2] = -front.y;
	rotation[2][2] = -front.z;

	return rotation * translation;//从右向左阅读（先平移，然后旋转）
}

static void _camera_setup(opengl_camera_t* camera) {
	glm::vec3 front;
	front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
	front.y = sin(glm::radians(camera->pitch));
	front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
	
	camera->front = glm::normalize(front);
	camera->right = glm::normalize(glm::cross(camera->front, camera->world_up));
	camera->up = glm::normalize(glm::cross(camera->right, camera->front));

	camera->view = glm::mat4(1.0f);
	//这里camera->up也可以是camera->world_up，只不过我们已经计算出了camera->up。
	//camera->view = glm::lookAt(camera->pos, camera->pos + camera->front, camera->up);
	camera->view = mylookAt(camera->pos, camera->pos + camera->front, camera->world_up);

	camera->projection = glm::mat4(1.0f);
	camera->projection = glm::perspective(glm::radians(camera->zoom), camera->aspect, 0.1f, 100.0f);
}

void opengl_camera_init(opengl_camera_t* camera, glm::vec3 pos, float pitch, float yaw, float aspect) {
	camera->pos = pos;
	camera->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
	camera->yaw = yaw;
	camera->pitch = pitch;
	camera->sensitivity = 0.1f;
	camera->zoom = 45.0f;
	camera->aspect = aspect;

	_camera_setup(camera);
}

void opengl_camera_move(opengl_camera_t* camera, opengl_camera_movement_t movement) {
	float speed = 0.1f;

	if (movement == FORWARD) {
		camera->pos += speed * camera->front;
	}
	if (movement == BACKWARD) {
		camera->pos -= speed * camera->front;
	}
	if (movement == LEFT) {
		camera->pos -= speed * camera->right;
	}
	if (movement == RIGHT) {
		camera->pos += speed * camera->right;
	}
	_camera_setup(camera);
}

void opengl_camera_zoom(opengl_camera_t* camera, float zoom_offset) {
	camera->zoom -= (float)zoom_offset;
	if (camera->zoom < 1.0f)
		camera->zoom = 1.0f;
	if (camera->zoom > 45.0f)
		camera->zoom = 45.0f;
	_camera_setup(camera);
}

void opengl_camera_rotate(opengl_camera_t* camera, float yaw_offset, float pitch_offset) {
	yaw_offset *= camera->sensitivity;
	pitch_offset *= camera->sensitivity;

	camera->yaw += yaw_offset;
	camera->pitch += pitch_offset;

	if (camera->pitch > 89.0f)
		camera->pitch = 89.0f;
	if (camera->pitch < -89.0f)
		camera->pitch = -89.0f;

	_camera_setup(camera);
}