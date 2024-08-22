_Pragma("once");

typedef struct triangle_ctx_s {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int shaderProgram;
	unsigned int vertexShader;
	unsigned int fragmentShader;
}triangle_ctx_t;

extern void triangle_create(triangle_ctx_t* ctx);
extern void triangle_draw(triangle_ctx_t* ctx);
extern void triangle_destroy(triangle_ctx_t* ctx);