_Pragma("once")

typedef struct rectangle_ctx_s {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int shaderProgram;
	unsigned int vertexShader;
	unsigned int fragmentShader;
}rectangle_ctx_t;

extern void rectangle_create(rectangle_ctx_t* ctx);
extern void rectangle_draw(rectangle_ctx_t* ctx);
extern void rectangle_destroy(rectangle_ctx_t* ctx);