_Pragma("once")

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

typedef enum opengl_camera_movement_e {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
}opengl_camera_movement_t;

typedef struct opengl_camera_s {
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;
	glm::mat4 view;
	glm::mat4 projection;
	float yaw;
	float pitch;
	float sensitivity;
	float zoom;
	float aspect;
}opengl_camera_t;

typedef struct opengl_ctx_s {
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int shader_program;
	unsigned int textures[16];	//opengl 3.3 着色器最多可以加载16个纹理
	unsigned int viewport_width;
	unsigned int viewport_height;
	opengl_camera_t camera;
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
	TYPE_COORDS_02,
	TYPE_CAMERA_01,
	TYPE_CAMERA_02,
	TYPE_CAMERA_03,
}opengl_scene_type_t;

extern void opengl_shader_program_create(opengl_ctx_t* ctx, opengl_scene_type_t type);
extern void opengl_shader_program_use(opengl_ctx_t* ctx);
extern void opengl_shader_program_destroy(opengl_ctx_t* ctx);

extern void opengl_scene_create(opengl_ctx_t* ctx, opengl_scene_type_t type);
extern void opengl_scene_draw(opengl_ctx_t* ctx, opengl_scene_type_t type);
extern void opengl_scene_destroy(opengl_ctx_t* ctx);

extern void opengl_camera_init(opengl_camera_t* camera, glm::vec3 pos, float pitch, float yaw, float aspect);
extern void opengl_camera_move(opengl_camera_t* camera, opengl_camera_movement_t movement);
extern void opengl_camera_zoom(opengl_camera_t* camera, float zoom_offset);
extern void opengl_camera_rotate(opengl_camera_t* camera, float yaw_offset, float pitch_offset);
