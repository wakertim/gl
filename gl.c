#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "types.h"
#include "shader.h"
#include "umalloc.h"
#include "matrix.h"
#include "math.h"

#define GL_LOAD_FUNCTION_POINTERS
#include "gl_load_util.h"
shader_t *shader_g;
Mat4 rotate_matrix;
Mat4 scale_matrix;

f32 quad[] = {
	0.5, 0.5f, 0.0f,	 // 0
	-0.5, 0.5f, 0.0f,	 // 1
	-0.5, -0.5f, 0.0f,	 // 2
	0.5, -0.5f, 0.0f,	 // 3

	0.5, 0.5f, 1.0f,	 // 4
	-0.5, 0.5f, 1.0f,	 // 5
	-0.5, -0.5f, 1.0f,	 // 6
	0.5, -0.5f, 1.0f,	 // 7
};
u32 elements_quad[] = {
	0,1,2,2,3,0,  // Front

	4,5,6,6,7,4,  // Back
};

f32 triangle [] = {
		0.0f, 	 0.5f, 1.0f,
	   -0.5f,	-0.5f, 1.0f,
		0.5f,	-0.5f, 1.0f,
};

GLuint element_data[6] = {0, 1, 2, 3, 4, 5};

void hotreload_shader() {
	shader_create("shader/vert.glsl", "shader/frag.glsl");
}

u32
element_buffer_create(u32 num, void *data) 
{
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * num, data, GL_STATIC_DRAW);
	return ebo;
}

u32
array_buffer_create(u32 num, u32 total_elements, u32 offset, void *data)
{
	u32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * total_elements, data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, num, GL_FLOAT, GL_FALSE, sizeof(f32) * num, (void*)offset); 
	glEnableVertexAttribArray(0);

	return vbo;
}

void
gl_input(char ch) 
{
	f32 translate_value = 0.1f;
	static float xval, yval, zval;
	if (ch == 'a') {
		xval -= translate_value;
		shader_set1f(shader_g, "u_xoffset", xval);
	}

	if (ch == 'u') {
		zval += translate_value;
		shader_set1f(shader_g, "u_zoffset", zval);
	}

	if (ch == 'f') {
		zval -= translate_value;
		shader_set1f(shader_g, "u_zoffset", zval);
	}
	if (ch == 'd') {
		xval += translate_value;
		shader_set1f(shader_g, "u_xoffset", xval);
	}

	if (ch == 's') {
		yval -= translate_value;
		shader_set1f(shader_g, "u_yoffset", yval);
	}
	if (ch == 'w') {
		yval += translate_value;
		shader_set1f(shader_g, "u_yoffset", yval);
	}

	/*	
	if (ch == 'r') {
		shader_set4fv(shader_g, "rotate_matrix", yval);
	}
	*/
	
}

void
gl_draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

void
gl_init() 
{
	/* load all funtion ponters */
	gl_load_util();

	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_ALWAYS); 

	u32 vao;
	u32 offset = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	u32 vbo = array_buffer_create(3, 24, offset, quad);
	u32 ebo = element_buffer_create(12, elements_quad);
	glBindVertexArray(0);

	shader_g = 
	shader_create("shader/vert.glsl", "shader/frag.glsl");
	shader_use(shader_g);
	shader_set4f(shader_g, "uniform_color", 0.3f, 0.2f, 0.5f, 1.0f);

	Mat4 translate_matrix = Mat4ranslate(mat4_create(1.0f), 0.0f, 0.0f, 0.0f);
	scale_matrix = mat4_scale(mat4_create(1.0f), 1.0f, 1.0f, 1.0f);
	rotate_matrix = mat4_rotate_z(mat4_create(1.0f), 45.0f);
	//Mat4 view_matrix = mat4_view(45.0f, 0.1f, 1000.0f);

	mat4_print(rotate_matrix);
	shader_set4fv(shader_g, "translate_matrix", translate_matrix);
	shader_set4fv(shader_g, "scale_matrix", scale_matrix);
	shader_set4fv(shader_g, "rotate_matrix", rotate_matrix);
	//shader_set4fv(shader_g, "view_matrix", view_matrix);

	shader_set1f(shader_g, "u_yoffset", 0.0f);
	shader_set1f(shader_g, "u_xoffset", 0.0f);
	shader_set1f(shader_g, "u_zoffset", 0.0f);
	glBindVertexArray(vao);
}

void
gl_terminate()
{
	shader_destroy(shader_g);
}
