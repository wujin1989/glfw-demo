_Pragma("once")

typedef struct opengl_ctx_s {
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int shader_program;
	unsigned int textures[16];	//opengl 3.3 着色器最多可以加载16个纹理
}opengl_ctx_t;

typedef enum opengl_scene_type_e {
	TYPE_TRIANGLE_01,
	TYPE_TRIANGLE_02,
	TYPE_RECTANGLE_01,
	TYPE_RECTANGLE_02,
	TYPE_TEXTURE_01,
	TYPE_TEXTURE_02,
	TYPE_MATRIX_01,
	TYPE_MATRIX_02,
	TYPE_COORDS_01,
}opengl_scene_type_t;

extern void opengl_shader_program_create(opengl_ctx_t* ctx, opengl_scene_type_t type);
extern void opengl_shader_program_use(opengl_ctx_t* ctx);
extern void opengl_shader_program_destroy(opengl_ctx_t* ctx);

extern void opengl_scene_create(opengl_ctx_t* ctx, opengl_scene_type_t type);
extern void opengl_scene_draw(opengl_ctx_t* ctx, opengl_scene_type_t type);
extern void opengl_scene_destroy(opengl_ctx_t* ctx, opengl_scene_type_t type);