#ifndef MATRIX_H
#define MATRIX_H

#include "types.h"

Mat4 mat4_identity();
Mat4 mat4_create(f32 val);
Mat4 mat4_scale(Vec3 scalar);
Mat4 mat4_rotate_z(float angle);
Mat4 mat4_view(float angle, f32 near, f32 far);
void mat4_print(Mat4 mat);
Mat4 mat4_mul(Mat4 m1, Mat4 m2);
Mat4 mat4_perspective(float fov_radians, float aspect_ratio, f32 near, f32 far);

Mat4 mat4_inverse(Mat4 matrix);
Mat4 mat4_translation(Vec3 pos);

Vec4 mat4_mul_vec4(Mat4 m, Vec4 v);

void vec4_print(Vec4 v);

Vec4 vec4_create();


#endif // MATRIX_H

