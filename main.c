#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "platform.h"

#include "umalloc.h"

void gl_init();
void gl_draw();
void gl_terminate();

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


