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

Shader *shader_g;


Mat4 cameraGetViewMatrix(Camera *c) {
	return c->view_matrix;
}

Camera* cameraCreate() {
	Camera *c = malloc(sizeof(Camera));
	memset(c, 0, sizeof(Camera));
	c->position.data[0] = 0.0f;
	c->position.data[1] = 0.0f;
	c->position.data[2] = 0.0f;

	c->rotation.data[0] = 0.0f;
	c->rotation.data[1] = 0.0f;
	c->rotation.data[2] = 0.0f;
	c->view_matrix = mat4_identity();
	c->view_matrix = mat4_inverse(c->view_matrix);
	return c;
}

Mat4 model_g;

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
	shader_create("vert.glsl", "frag.glsl");
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
	f32 translate_value = 1.0f;
	static float xval, yval, zval;
	if (ch == 'a') {
	//	camera_g = mat4_mul(camera_g, mat4_translation((Vec3){0.1f, 0.0f, 0.0f}));
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
	glEnable(GL_CULL_FACE);  
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glDepthFunc(GL_ALWAYS); 

	u32 vao;
	u32 offset = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	u32 vbo = array_buffer_create(3, 24, offset, quad);
	u32 ebo = element_buffer_create(12, elements_quad);
	glBindVertexArray(0);

	shader_g = 
	shader_create("vert.glsl", "frag.glsl");
	shader_use(shader_g);
	shader_set4f(shader_g, "uniform_color", 0.3f, 0.2f, 0.5f, 1.0f);

	model_g = mat4_identity();
	model_g = mat4_mul(model_g, mat4_translation((Vec3){0.0f, 0.0f, 1.0f}));
	model_g = mat4_mul(model_g, mat4_scale((Vec3){1.0f, 1.0f, 1.0f}));
	model_g = mat4_mul(model_g, mat4_rotate_z(45.0f));

	Camera *c = cameraCreate();
	Mat4 perspective = mat4_perspective(PI/2, 1.0f, 0.1f, 1000.0f);

	shader_set4fv(shader_g, "M", model_g);
	shader_set4fv(shader_g, "P" , perspective);
	shader_set4fv(shader_g, "V" , cameraGetViewMatrix(c));

	glBindVertexArray(vao);
}

void
gl_terminate()
{
	shader_destroy(shader_g);
}
