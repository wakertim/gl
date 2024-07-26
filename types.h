#ifndef TYPES_H
#define TYPES_H

#define true 1
#define false 0

#define PI 3.141593

typedef unsigned char b8;
typedef unsigned int u32;
typedef unsigned long long int u64;
typedef signed int i32;
typedef float f32;
typedef double f64;

typedef struct mat4_t {
	f32 buf[4][4];
} mat4_t;

typedef struct vec4_t {
	f32 data[4];
} vec4_t;

	
#endif // TYPES_H
