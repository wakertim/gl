#version 330 core

in vec3 fcolor;
out vec4 out_color;

void main() {
	out_color = vec4(fcolor.xyz, 1.0f);
}

