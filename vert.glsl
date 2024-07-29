#version 330 core

layout (location = 0) in vec3 pos;

out vec3 fcolor;

uniform vec4 uniform_color;
uniform mat4 M;
uniform mat4 P;
uniform mat4 V;

void main() {
	gl_Position = P*V*M*vec4(pos, 1.0f);
	fcolor = vec3(uniform_color.xyz);
}
