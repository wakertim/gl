#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "shader.h"
#include "gl_load_util.h"
#include "umalloc.h"

void 
shader_set1f(shader_t *shader, const char *str, f32 val)
{
	glUniform1f(glGetUniformLocation(shader->program, str), val);
}

void
shader_set4f(shader_t *shader,const char *str, f32 v0 ,f32 v1 ,f32 v2 ,f32 v3)
{
	glUniform4f(glGetUniformLocation(shader->program, str), v0 ,v1 ,v2 ,v3);
}

void
shader_set4fv(shader_t *shader, const char *str, mat4_t mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->program, str),1, GL_TRUE, (const GLfloat*)mat.buf);
}

shader_t*
shader_create(const char *filename_vertex, const char *filename_fragment)
{
	FILE *v_ptr = fopen(filename_vertex, "r");
	FILE *f_ptr = fopen(filename_fragment, "r");
	if (v_ptr == NULL || f_ptr == NULL) {
		printf("fopen() failed\n");
		return NULL;
	}

	shader_t *tmp = ALLOC(sizeof(shader_t), MEMORY_STATS_TAG_SHADER);
	
	tmp->filename_vertex =		ALLOC(sizeof(char) * 50, MEMORY_STATS_TAG_STRING);
	tmp->filename_fragment =	ALLOC(sizeof(char) * 50, MEMORY_STATS_TAG_STRING);
	memcpy(tmp->filename_vertex, filename_vertex, sizeof(char) * 50);
	memcpy(tmp->filename_fragment, filename_fragment, sizeof(char) * 50);

	char ch;
	char vbuffer[512];
	char fbuffer[512];
	char *vbuf = vbuffer;
	char *fbuf = fbuffer;
	int i = 0;
	for (i = 0; ((ch = getc(v_ptr)) != EOF); ++i) {
		vbuffer[i] = ch;
	}
	vbuffer[i - 1] = '\0'; /* TODO: Assumes endind char is \n */

	for (i = 0; ((ch = getc(f_ptr)) != EOF); ++i) {
		fbuffer[i] = ch;
	}
	fbuffer[i - 1] = '\0'; /* TODO: Assumes endind char is \n */

	fseek(v_ptr, 0, SEEK_SET);
	fseek(f_ptr, 0, SEEK_SET);

	tmp->vhandle = glCreateShader(GL_VERTEX_SHADER);
	tmp->fhandle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(tmp->vhandle, 1, &vbuf, NULL); 
	glShaderSource(tmp->fhandle, 1, &fbuf, NULL); 

	glCompileShader(tmp->vhandle);
	int  success;
	char infolog[512];
	glGetShaderiv(tmp->vhandle, GL_COMPILE_STATUS, &success);
	if(!success) {
		    glGetShaderInfoLog(tmp->vhandle, 512, NULL, infolog);
			printf("vertex shader compile error '%s'\n", infolog);
			return NULL;
	}

	glCompileShader(tmp->fhandle);
	glGetShaderiv(tmp->fhandle, GL_COMPILE_STATUS, &success);
	if(!success) {
		    glGetShaderInfoLog(tmp->fhandle, 512, NULL, infolog);
			printf("fragment shader compile error '%s'\n", infolog);
			return NULL;
	}

	tmp->program = glCreateProgram();
	glAttachShader(tmp->program, tmp->vhandle);
	glAttachShader(tmp->program, tmp->fhandle);
	glLinkProgram(tmp->program);

	return tmp;
}

void
shader_destroy(shader_t *shader)
{
	glDeleteShader(shader->vhandle);
	glDeleteShader(shader->fhandle);

	FREE(shader->filename_vertex,	sizeof(char) * 50,	MEMORY_STATS_TAG_STRING);
	FREE(shader->filename_fragment, sizeof(char) * 50,	MEMORY_STATS_TAG_STRING);

	FREE(shader,					sizeof(shader_t),	MEMORY_STATS_TAG_SHADER);
}

void
shader_use(shader_t *shader)
{
	glUseProgram(shader->program);
}
