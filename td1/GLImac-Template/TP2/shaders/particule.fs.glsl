#version 330 core

in vec3 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;

void main() {
	float alpha = 2.5;
	float beta = 80;
	float a =  alpha * exp( - beta * (distance(vFragPosition, vec2(0, 0)) * distance(vFragPosition, vec2(0, 0))) );
	fFragColor = vFragColor * a;
};