#version 330 core

in vec3 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;

void main() {
	fFragColor = vFragColor * smoothstep(1, 0.2, length(fract(5.0 * vFragPosition) - 0.5));
};