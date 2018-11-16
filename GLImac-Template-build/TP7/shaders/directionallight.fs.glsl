#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

vec3 blinnPhong() {
	return uLightIntensity * (uKd * glm::dot((normalize(uLightDir_vs), vNormal_vs)) 
		+ uKs * pow((glm::dot((normalize(-vPosition_vs) + normalize(uLightDir_vs)) / 2, vNormal_vs)), uShininess));
}

void main() {
	// fFragColor = (texture(uEarthTexture, vTexCoords)).xyz + (texture(uCloudTexture, vTexCoords)).xyz;
	fFragColor = blinnPhong();
};