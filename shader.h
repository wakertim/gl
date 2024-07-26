#ifndef SHADER_H
#define SHADER_H
#include "types.h"

typedef struct {
	u32 program;
	u32 ulocation;
	char *filename_vertex;
	char *filename_fragment;
	u32 vhandle;
	u32 fhandle;
} shader_t;

shader_t*
shader_create(const char *filename_vertex, const char *filename_fragment);

void
shader_destroy(shader_t *shader_g);

void 
shader_set1f(shader_t *shader, const char *str, f32 val);
void
shader_set4f(shader_t *shader,const char *str, f32 v0 ,f32 v1 ,f32 v2 ,f32 v3);

void shader_set4fv(shader_t *shader, const char *str, mat4_t mat);

void
shader_use(shader_t *shader);

#endif /* SHADER_H */
