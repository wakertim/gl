#version 330 core

layout (location = 0) in vec3 pos;

out vec3 fcolor;

uniform vec4 uniform_color;
uniform mat4 translate_matrix;
uniform mat4 scale_matrix;
uniform mat4 rotate_matrix;

uniform float u_yoffset;
uniform float u_xoffset;
uniform float u_zoffset;

void main() {
	vec4 new_pos = translate_matrix * scale_matrix * rotate_matrix *  vec4(pos.x, pos.y, pos.z, 1.0f);
	gl_Position = vec4(new_pos.x + u_xoffset, new_pos.y + u_yoffset, new_pos.z + u_zoffset, 1.0f);
	fcolor = vec3(uniform_color.xyz);
}
