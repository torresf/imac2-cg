#version 330 core

in vec2 vFragTexture;

out vec3 fFragColor;

void main() {
	// fFragColor = vec3(vFragTexture, 1);
	fFragColor = vec3(1, 0, 0);
};