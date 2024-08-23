#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.h"
#include <stdio.h>

int get_max_vertex_attrs_num(void) {
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	printf("Maximum nr of vertex attributes supported: %d\n", nrAttributes);
	return nrAttributes;
}