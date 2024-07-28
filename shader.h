#ifndef SHADER_H
#define SHADER_H
#include "types.h"

typedef struct Shader {
	u32 program;
	u32 ulocation;
	char *filename_vertex;
	char *filename_fragment;
	u32 vhandle;
	u32 fhandle;
} Shader;

Shader*
shader_create(const char *filename_vertex, const char *filename_fragment);

void
shader_destroy(Shader *shader_g);

void 
shader_set1f(Shader *shader, const char *str, f32 val);

void
shader_set4f(Shader *shader,const char *str, f32 v0 ,f32 v1 ,f32 v2 ,f32 v3);

void shader_set4fv(Shader *shader, const char *str, Mat4 mat);

void
shader_use(Shader *shader);

#endif /* SHADER_H */
