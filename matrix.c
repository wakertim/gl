#include <stdio.h>
#include "matrix.h"
#include "types.h"
#include "math.h"

Mat4 mat4_create(f32 val)
{
	Mat4 m ={0};	
	m.buf[0][0] = 1.0f;
	m.buf[1][1] = 1.0f;
	m.buf[2][2] = 1.0f;
	m.buf[3][3] = 1.0f;
	return m;
}

Mat4
mat4_scale(Mat4 mat, f32 x, f32 y, f32 z) 
{
	mat.buf[0][0] *= x;
	mat.buf[1][1] *= y;
	mat.buf[2][2] *= z;
	return mat;
}

Mat4
mat4_view(float angle, f32 near, f32 far)
{
	f32 val = (PI/180);
	f32 c = cosf(val * (angle/2)) / sinf(val * (angle/2));
	Mat4 mat = {0};	
	mat.buf[0][0] = c;
	mat.buf[1][1] = c;
	mat.buf[2][2] = ((far + near)/(far - near));
	mat.buf[2][3] = -1.0f;
	mat.buf[3][2] = ((far * near * 2) / (far - near));
	return mat;
}

Mat4
mat4_rotate_z(Mat4 mat, float angle)
{
	f32 val = PI/180;
	mat.buf[0][0] =  cosf(val * angle);
	mat.buf[0][1] = -sinf(val * angle);
	mat.buf[1][0] =  sinf(val * angle);
	mat.buf[1][1] =  cosf(val * angle);
	//mat.buf[1][1] =	 cosf(	(PI/180) * angle);
	//mat.buf[1][2] = -sinf(	(PI/180) * angle);
	//mat.buf[2][1] =	 sinf(	(PI/180) * angle);
	//mat.buf[2][2] = -cosf(	(PI/180) * angle);
	return mat;
}


Mat4
Mat4ranslate(Mat4 mat, f32 x, f32 y, f32 z)
{
	mat.buf[0][3] = x;
	mat.buf[1][3] = y;
	mat.buf[2][3] = z;
	
	return mat;
}

vec4_t
mat4_mul_vec4(Mat4 m, vec4_t v) 
{
	for (int i = 0; i < 4; ++i) {
		f32 sum = 0.0f;
		for (int j = 0; j < 4; ++j) {
			sum += (m.buf[i][j] * v.data[j]);
		}
		v.data[i] = sum;
	}
	return v;
}

vec4_t
vec4_create()
{
	vec4_t v = {0};
	v.data[3] = 1.0f;
	return v;
}

void vec4_print(vec4_t v) 
{
	printf("vec4 print_out\n");
	printf("|");
	for (int i = 0; i < 4; ++i) {
		printf("%.2f ", v.data[i]);
	}
	printf("|\n");
}


void 
mat4_print(Mat4 mat)
{
	for (int i = 0; i < 4; ++i) {
		printf("|");
		for (int j = 0; j < 4; ++j) {
			printf("%.2f ", mat.buf[i][j]);
		}
		printf("|\n");
	}
}

