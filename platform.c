#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glxext.h>

#include "types.h"

void gl_input(char ch);

typedef struct {
	Display *display;		
	i32 screen;
	Window window;
	GLXContext glx_context;
} X11_Window;
static X11_Window state_window;

static void x11_window_create(u32 height, u32 width, const char *title) {
	state_window.display = XOpenDisplay(NULL);
	if (state_window.display == NULL) {
		printf("XOpenDisplay() failed\n");
		exit(1);
	}

	GLint major, minor = 0;
	glXQueryVersion(state_window.display, &major, &minor);
	printf("GLX version: %d.%d\n", major, minor);

	Window root_window	= DefaultRootWindow(state_window.display);
	state_window.screen	= DefaultScreen(state_window.display);

	GLint gl_attributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	XVisualInfo *xvisual = glXChooseVisual(state_window.display, 0, gl_attributes);
	if (xvisual == NULL) {
		printf("glXChooseVisual() == NULL\n");
		exit(1);
	}

	Colormap colormap = XCreateColormap(state_window.display, root_window, xvisual->visual, AllocNone);
	XSetWindowAttributes attributes = {
		.event_mask = KeyPressMask | ExposureMask,
		.colormap = colormap,
	};

	state_window.window = XCreateWindow(
			state_window.display,
			DefaultRootWindow(state_window.display),
			0, 0, width, height, 
			0,xvisual->depth , InputOutput, CopyFromParent, CWEventMask,
			&attributes
	);

	state_window.glx_context = glXCreateContext(state_window.display, xvisual, NULL, GL_TRUE);
	glXMakeCurrent(state_window.display, state_window.window, state_window.glx_context);

	XStoreName(state_window.display, state_window.window, title);
	XSelectInput(state_window.display, state_window.window, ExposureMask | KeyPressMask);
	XMapWindow(state_window.display, state_window.window);
	XFlush(state_window.display);
}

static void x11_window_destroy() {
	glXMakeCurrent(state_window.display, None, NULL);
	glXDestroyContext(state_window.display, state_window.glx_context);
	XDestroyWindow(state_window.display, state_window.window);

	XCloseDisplay(state_window.display);
}

static b8 x11_window_messages() {
	XEvent event;

	if (XCheckMaskEvent(state_window.display, KeyPressMask, &event)) {
//		XNextEvent(state_window.display, &event);
		printf("key pressed '%d'\n", event.xkey.keycode);

		if (event.xkey.keycode == 38) {
			gl_input('a');	
		} else if (event.xkey.keycode == 39) {
			gl_input('s');	
		} else if (event.xkey.keycode == 30) {
			gl_input('u');	
		} else if (event.xkey.keycode == 41) {
			gl_input('f');	
		} else if (event.xkey.keycode == 40) {
			gl_input('d');	
		} else if (event.xkey.keycode == 25) {
			gl_input('w');	
		} else if (event.xkey.keycode == 24) { // quit on 'q'
			return false;
		}
	}

	return true;
}

static b8 x11_window_swap_image() {
	glXSwapBuffers(state_window.display, state_window.window);
	return true;
}

void platform_update() {
	x11_window_swap_image();
}

void platform_terminate() {
	x11_window_destroy();
}

b8 platform_messages() {
	return x11_window_messages();
}

void platform_init() {
	x11_window_create(800, 800, "title");
}
