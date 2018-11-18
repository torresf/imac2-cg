#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform vec3 uLightIntensity;
uniform vec3 uLightPos_vs;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

out vec3 fFragColor;

vec3 blinnPhong() {
	vec3 w0 = normalize(-vPosition_vs);
	vec3 wi = normalize(uLightPos_vs - vPosition_vs);
	float d = distance(uLightPos_vs, vPosition_vs);
	vec3 Li = uLightIntensity / (d * d);
	vec3 halfVector = (w0 + wi) / 2;
	vec3 N = vNormal_vs;
	return Li * (uKd * dot(wi, N) + uKs * pow((dot(halfVector, N)), uShininess));
}

void main() {
	if (uKs == vec3(1, 1, 1))
		fFragColor = vec3(1, 1, 1);
	else 
		fFragColor = blinnPhong();
};