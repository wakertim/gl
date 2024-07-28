#include <stdio.h>
#include "matrix.h"
#include "types.h"
#include "math.h"
#include "string.h"

Mat4 mat4_mul(Mat4 mat1, Mat4 mat2) {
	Mat4 out_mat = mat4_identity();

	f32 *m1 = mat1.data;
	f32 *m2 = mat2.data;
	f32 *ptr = out_mat.data;

	for (u32 i = 0; i < 4; ++i) {
		for (u32 j = 0; j < 4; ++j) {
			*ptr = 	m1[0] * m2[0 + j] + 
				m1[1] * m2[4 + j] +
				m1[2] * m2[8 + j] +
				m1[3] * m2[12 + j]; 
			ptr++;
		}
		m1 += 4;
	}
	return out_mat;
}

Mat4 mat4_identity() {
	Mat4 m ={0};	
	memset(&m, 0, sizeof(Mat4));
	m.data[0] = 1.0f;
	m.data[5] = 1.0f;
	m.data[10] = 1.0f;
	m.data[15] = 1.0f;
	return m;
}

Mat4 mat4_create(f32 val) {
	Mat4 m ={0};	
	memset(&m, 0, sizeof(Mat4));
	m.data[0] = val;
	m.data[5] = val;
	m.data[10] = val;
	m.data[15] = val;
	return m;
}

Mat4 mat4_scale(Vec3 scalar) {
	Mat4 out_mat = mat4_identity();
	out_mat.data[0] = scalar.data[0];
	out_mat.data[5] = scalar.data[1];
	out_mat.data[10] = scalar.data[2];
	return out_mat;
}

Mat4 mat4_inverse(Mat4 matrix) {
	const f32 *m = matrix.data;
	f32 t0 = m[10] * m[15];
	f32 t1 = m[14] * m[11];
	f32 t2 = m[6] * m[15];
	f32 t3 = m[14] * m[7];
	f32 t4 = m[6] * m[11];
	f32 t5 = m[10] * m[7];
	f32 t6 = m[2] * m[15];
	f32 t7 = m[14] * m[3];
	f32 t8 = m[2] * m[11];
	f32 t9 = m[10] * m[3];
	f32 t10 = m[2] * m[7];
	f32 t11 = m[6] * m[3];
	f32 t12 = m[8] * m[13];
	f32 t13 = m[12] * m[9];
	f32 t14 = m[4] * m[13];
	f32 t15 = m[12] * m[5];
	f32 t16 = m[4] * m[9];
	f32 t17 = m[8] * m[5];
	f32 t18 = m[0] * m[13];
	f32 t19 = m[12] * m[1];
	f32 t20 = m[0] * m[9];
	f32 t21 = m[8] * m[1];
	f32 t22 = m[0] * m[5];
	f32 t23 = m[4] * m[1];

	Mat4 out_matrix;
	f32 *o = out_matrix.data;
	o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) - (t1 * m[5] + t2 * m[9] + t5 * m[13]);
	o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) - (t0 * m[1] + t7 * m[9] + t8 * m[13]);
	o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) - (t3 * m[1] + t6 * m[5] + t11 * m[13]);
	o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) - (t4 * m[1] + t9 * m[5] + t10 * m[9]);

	f32 d = 1.0f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);

	o[0] = d * o[0];
	o[1] = d * o[1];
	o[2] = d * o[2];
	o[3] = d * o[3];

	o[4] = d * ((t1 * m[4] + t2 * m[8] + t5 * m[12]) - (t0 * m[4] + t3 * m[8] + t4 * m[12]));
	o[5] = d * ((t0 * m[0] + t7 * m[8] + t8 * m[12]) - (t1 * m[0] + t6 * m[8] + t9 * m[12]));
	o[6] = d * ((t3 * m[0] + t6 * m[4] + t11 * m[12]) - (t2 * m[0] + t7 * m[4] + t10 * m[12]));
	o[7] = d * ((t4 * m[0] + t9 * m[4] + t10 * m[8]) - (t5 * m[0] + t8 * m[4] + t11 * m[8]));
	o[8] = d * ((t12 * m[7] + t15 * m[11] + t16 * m[15]) - (t13 * m[7] + t14 * m[11] + t17 * m[15]));
	o[9] = d * ((t13 * m[3] + t18 * m[11] + t21 * m[15]) - (t12 * m[3] + t19 * m[11] + t20 * m[15]));
	o[10] = d * ((t14 * m[3] + t19 * m[7] + t22 * m[15]) - (t15 * m[3] + t18 * m[7] + t23 * m[15]));
	o[11] = d * ((t17 * m[3] + t20 * m[7] + t23 * m[11]) - (t16 * m[3] + t21 * m[7] + t22 * m[11]));
	o[12] = d * ((t14 * m[10] + t17 * m[14] + t13 * m[6]) - (t16 * m[14] + t12 * m[6] + t15 * m[10]));
	o[13] = d * ((t20 * m[14] + t12 * m[2] + t19 * m[10]) - (t18 * m[10] + t21 * m[14] + t13 * m[2]));
	o[14] = d * ((t18 * m[6] + t23 * m[14] + t15 * m[2]) - (t22 * m[14] + t14 * m[2] + t19 * m[6]));
	o[15] = d * ((t22 * m[10] + t16 * m[2] + t21 * m[6]) - (t20 * m[6] + t23 * m[10] + t17 * m[2]));

	return out_matrix;
}

Mat4 mat4_perspective(float fov_radians, float aspect_ratio, f32 near, f32 far) {
	Mat4 out_mat = mat4_identity();

	f32 half_tan = tanf(fov_radians * 0.5f);

	out_mat.data[0] = 1.0f / (aspect_ratio * half_tan);
	out_mat.data[5] = 1.0f / half_tan;
	//out_mat.data[10] = //((far + near)/(far - near));
	out_mat.data[10] = 1.0f;
	out_mat.data[14] = 1.0f;//((2*far*near)/(far - near)
	out_mat.data[15] = 0.0f;
	return out_mat;
}


Mat4 mat4_rotate_z(float angle) {
	Mat4 out_mat = mat4_identity();
	f32 val = PI/180;
	f32 c = cosf(val * angle);
	f32 s = sinf(val * angle);
	out_mat.data[0] =  c;
	out_mat.data[1] = -s;
	out_mat.data[4] =  s;
	out_mat.data[5] =  c;
	return out_mat;
}

Mat4 mat4_translation(Vec3 pos) {
	Mat4 out_mat = mat4_identity();
	out_mat.data[3] = pos.data[0];
	out_mat.data[7] = pos.data[1];
	out_mat.data[11] = pos.data[2];
	return out_mat;
}

Vec4 vec4_create() {
	Vec4 v = {0};
	memset(&v, 0, sizeof(Vec4));
	v.data[3] = 1.0f;
	return v;
}

void vec4_print(Vec4 v) {
	printf("vec4 print_out\n");
	printf("|");
	for (int i = 0; i < 4; ++i) {
		printf("%.2f ", v.data[i]);
	}
	printf("|\n");
}

void mat4_print(Mat4 mat) {
	printf("---------------\n");
	printf("|%0.2f  %0.2f  %0.2f  %0.2f\n",mat.data[0],mat.data[1],mat.data[2],mat.data[3]); 
	printf("|%0.2f  %0.2f  %0.2f  %0.2f\n",mat.data[4],mat.data[5],mat.data[6],mat.data[7]); 
	printf("|%0.2f  %0.2f  %0.2f  %0.2f\n",mat.data[8],mat.data[9],mat.data[10],mat.data[11]); 
	printf("|%0.2f  %0.2f  %0.2f  %0.2f\n",mat.data[12],mat.data[13],mat.data[14],mat.data[15]); 
	printf("---------------\n");
}

