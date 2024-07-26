#ifndef GL_LOAD_H
#define GL_LOAD_H

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef unsigned int	GLenum;
typedef unsigned char	GLboolean;
typedef unsigned int	GLbitfield;
typedef void			GLvoid;
typedef signed char		GLbyte;		/* 1-byte signed */
typedef short			GLshort;	/* 2-byte signed */
typedef int				GLint;		/* 4-byte signed */
typedef unsigned char	GLubyte;	/* 1-byte unsigned */
typedef unsigned short	GLushort;	/* 2-byte unsigned */
typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef int				GLsizei;	/* 4-byte signed */
typedef float			GLfloat;	/* single precision float */
typedef float			GLclampf;	/* single precision float in [0,1] */
typedef double			GLdouble;	/* double precision float */
typedef double			GLclampd;	/* double precision float in [0,1] */
typedef char			GLchar;		/*GL_VERSION_3_3*/
typedef long int		GLsizeiptr; /*Custom*/

#define GL_FALSE						0
#define GL_TRUE							1

#define GL_POINTS						0x0000
#define GL_LINES						0x0001
#define GL_LINE_LOOP					0x0002
#define GL_LINE_STRIP					0x0003
#define GL_TRIANGLES					0x0004
#define GL_TRIANGLE_STRIP				0x0005
#define GL_TRIANGLE_FAN					0x0006
#define GL_QUADS						0x0007
#define GL_QUAD_STRIP					0x0008
#define GL_POLYGON						0x0009

#define GL_ARRAY_BUFFER                 0x8892
#define GL_ELEMENT_ARRAY_BUFFER         0x8893
#define GL_FRAGMENT_SHADER              0x8B30
#define GL_VERTEX_SHADER				0x8B31
#define GL_COMPILE_STATUS               0x8B81
#define GL_STATIC_DRAW                  0x88E4

#define GL_BYTE							0x1400
#define GL_UNSIGNED_BYTE				0x1401
#define GL_SHORT						0x1402
#define GL_UNSIGNED_SHORT				0x1403
#define GL_INT							0x1404
#define GL_UNSIGNED_INT					0x1405
#define GL_FLOAT						0x1406
#define GL_2_BYTES						0x1407
#define GL_3_BYTES						0x1408
#define GL_4_BYTES						0x1409
#define GL_DOUBLE						0x140A

/* glPush/PopAttrib bits */
#define GL_CURRENT_BIT				0x00000001
#define GL_POINT_BIT				0x00000002
#define GL_LINE_BIT				0x00000004
#define GL_POLYGON_BIT				0x00000008
#define GL_POLYGON_STIPPLE_BIT			0x00000010
#define GL_PIXEL_MODE_BIT			0x00000020
#define GL_LIGHTING_BIT				0x00000040
#define GL_FOG_BIT				0x00000080
#define GL_DEPTH_BUFFER_BIT			0x00000100
#define GL_ACCUM_BUFFER_BIT			0x00000200
#define GL_STENCIL_BUFFER_BIT			0x00000400
#define GL_VIEWPORT_BIT				0x00000800
#define GL_TRANSFORM_BIT			0x00001000
#define GL_ENABLE_BIT				0x00002000
#define GL_COLOR_BUFFER_BIT			0x00004000
#define GL_HINT_BIT				0x00008000
#define GL_EVAL_BIT				0x00010000
#define GL_LIST_BIT				0x00020000
#define GL_TEXTURE_BIT				0x00040000
#define GL_SCISSOR_BIT				0x00080000
#define GL_ALL_ATTRIB_BITS			0xFFFFFFFF

#define GL_DEPTH_BUFFER_BIT			0x00000100

/* Depth buffer */
#define GL_NEVER				0x0200
#define GL_LESS					0x0201
#define GL_EQUAL				0x0202
#define GL_LEQUAL				0x0203
#define GL_GREATER				0x0204
#define GL_NOTEQUAL				0x0205
#define GL_GEQUAL				0x0206
#define GL_ALWAYS				0x0207
#define GL_DEPTH_TEST				0x0B71
#define GL_DEPTH_BITS				0x0D56
#define GL_DEPTH_CLEAR_VALUE			0x0B73
#define GL_DEPTH_FUNC				0x0B74
#define GL_DEPTH_RANGE				0x0B70
#define GL_DEPTH_WRITEMASK			0x0B72
#define GL_DEPTH_COMPONENT			0x1902

	


/* Polygons */
#define GL_POINT				0x1B00
#define GL_LINE					0x1B01
#define GL_FILL					0x1B02
#define GL_CW					0x0900
#define GL_CCW					0x0901
#define GL_FRONT				0x0404
#define GL_BACK					0x0405
#define GL_POLYGON_MODE				0x0B40
#define GL_POLYGON_SMOOTH			0x0B41
#define GL_POLYGON_STIPPLE			0x0B42
#define GL_EDGE_FLAG				0x0B43
#define GL_CULL_FACE				0x0B44
#define GL_CULL_FACE_MODE			0x0B45
#define GL_FRONT_FACE				0x0B46
#define GL_POLYGON_OFFSET_FACTOR		0x8038
#define GL_POLYGON_OFFSET_UNITS			0x2A00
#define GL_POLYGON_OFFSET_POINT			0x2A01
#define GL_POLYGON_OFFSET_LINE			0x2A02
#define GL_POLYGON_OFFSET_FILL			0x8037

#define GL_FRONT_AND_BACK			0x0408

#define GL_FUNCTIONS_INFO																																			\
	X(void,		Clear,						GLbitfield																											)	\
	X(void,		ClearColor,					GLclampf,		GLclampf,			GLclampf,			GLclampf													)	\
	X(void,		GenBuffers, 				GLsizei,		GLuint*																								)	\
	X(void,		BindBuffer,					GLenum,			GLuint																								)	\
	X(void,		BufferData,					GLenum,			GLsizeiptr, 		const GLvoid*,		GLenum														)	\
	X(GLuint,	CreateShader,				GLenum																												)	\
	X(void,		ShaderSource,				GLuint,			GLsizei,			GLchar**,			GLint*														)	\
	X(void,		CompileShader,				GLuint																												)	\
	X(void,		GetShaderiv,				GLuint shader,	GLenum pname,		GLint *params																	)	\
	X(void,		GetShaderInfoLog,			GLuint shader,	GLsizei maxLength,	GLsizei *length,	GLchar *infoLog												)	\
	X(GLuint,	CreateProgram																																	)	\
	X(void,		AttachShader,				GLuint,			GLuint																								)	\
	X(void,		LinkProgram,				GLuint																												)	\
	X(void,		UseProgram,					GLuint																												)	\
	X(void,		DrawArrays,					GLenum mode,	GLint first,		GLsizei	count																	)	\
	X(void,		VertexAttribPointer,		GLuint index,	GLint size,			GLenum type,		GLboolean normalized,	GLsizei stride,		const GLvoid *	)	\
	X(void,		EnableVertexAttribArray,	GLuint index																										)	\
	X(void,		DisableVertexAttribArray,	GLuint index																										)	\
	X(void,		GenVertexArrays,			GLsizei n,		GLuint *arrays																						)	\
	X(void,		BindVertexArray,			GLuint array																										)	\
	X(void,		DrawElements,				GLenum mode,	GLsizei count,		GLenum type,		const void * indices										)	\
	X(void,		PolygonMode,				GLenum face,	GLenum mode																							)	\
	X(GLint,	GetUniformLocation,			GLuint program,	const GLchar *name																					)	\
	X(void,		Uniform4f,					GLint location, GLfloat v0,			GLfloat v1,			GLfloat v2,				GLfloat v3							)	\
	X(void,		Uniform1f,					GLint location, GLfloat v0																							)	\
	X(void,		DeleteShader,				GLuint shader																										)	\
	X(void,		UniformMatrix4fv,			GLint location,	GLsizei count,		GLboolean transpose,const GLfloat *value										)	\
	X(void,		GetUniformfv,				GLuint program, GLint location,		GLfloat *params																	)	\
	X(void,		Enable,						GLenum cap																											)	\
	X(void,		Disable,					GLenum cap																											)	\
	X(void,		DepthFunc,					GLenum func																											)	\

#ifdef GL_LOAD_FUNCTION_POINTERS
#define X(ret, name, ...)								\
	typedef ret(*PFN_gl##name)(__VA_ARGS__);			\
	PFN_gl##name gl##name = NULL;						\

	GL_FUNCTIONS_INFO
#undef X

void gl_load_util() {

	void *libGL = dlopen("libGL.so", RTLD_LAZY);
	if (libGL == NULL) {
		printf("dlopen() filed\n");
	}

	#define X(ret, name, ...)									\
		gl##name = dlsym(libGL, "gl" #name);					\
		if ( gl##name == NULL ) {								\
			printf("dlsym() failed to open gl functions\n");	\
			exit(1);											\
		}														\

		GL_FUNCTIONS_INFO
	#undef X
}

#else  /* GL_LOAD_FUNCTION_POINTERS */

#define X(ret, name, ...)								\
	typedef ret(*PFN_gl##name)(__VA_ARGS__);			\
	extern PFN_gl##name gl##name;						\

	GL_FUNCTIONS_INFO
#undef X	

#endif /* GL_LOAD_FUNCTION_POINTERS */
#endif /* GL_LOAD_H */
