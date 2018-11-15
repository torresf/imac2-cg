#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec2 vFragPosition;
out vec2 vFragNormal;
out vec3 vFragTexture;

void main() {
	vFragPosition = aVertexPosition;
	vFragColor = aVertexColor;
	gl_Position = vec4(aVertexPosition, 0, 1);
};