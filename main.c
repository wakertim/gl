#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "platform.h"
#include "umalloc.h"
#include "matrix.h"

void gl_init();
void gl_draw();
void gl_terminate();

int main2 ()
{
	Vec3 pos = {1.0f, 2.0f, 3.0f};
	Vec3 scalar = {10.0f, 10.0f, 10.0f};

	Mat4 scale 		= mat4_scale(scalar);
	Mat4 rotate		= mat4_rotate_z(180.0f);
	Mat4 translation 	= mat4_translation(pos);

	Mat4 model 	= mat4_identity();
	model = mat4_mul(model, translation);
	model = mat4_mul(model, rotate);
	model = mat4_mul(model, scale);

	return 0;
}

int main ()
{
	platform_init();	
	gl_init();

	while (platform_messages()) {
		gl_draw();
		platform_update();
	}

	platform_terminate();
	gl_terminate();
	uprint();
	
	return 0;
}


