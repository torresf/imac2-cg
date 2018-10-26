#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;
out vec2 vFragPosition;

mat3 translate(float tx, float ty) {
	return mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(tx, ty, 1));
}

mat3 scale(float sx, float sy) {
	return mat3(vec3(sx, 0, 0), vec3(0, sy, 0), vec3(0, 0, 1));
}

void main() {
	vFragPosition = aVertexPosition;
	vFragColor = aVertexColor;
	gl_Position = vec4((translate(.5, .5) * scale(2.5, 2.5) * vec3(aVertexPosition, 1)).xy, 0, 1);
};