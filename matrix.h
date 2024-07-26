#ifndef MATRIX_H
#define MATRIX_H
#include "types.h"

Mat4
mat4_create(f32 val);

Mat4
mat4_scale(Mat4 mat, f32 x, f32 y, f32 z);

Mat4
mat4_rotate_z(Mat4 mat, float angle);

Mat4
mat4_view(float angle, f32 near, f32 far);

void
mat4_print(Mat4 mat);

Mat4
mat4_make_identity();

Mat4
Mat4ranslate(Mat4 mat, f32 x, f32 y, f32 z);

vec4_t
mat4_mul_vec4(Mat4 m, vec4_t v);

void
vec4_print(vec4_t v);

vec4_t
vec4_create();


#endif // MATRIX_H

