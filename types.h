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

typedef struct Mat4{
	f32 data[16];
} Mat4;

typedef struct Vec4 {
	f32 x;
	f32 y;
	f32 z;
	f32 w;
} Vec4;

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

	
#endif // TYPES_H
