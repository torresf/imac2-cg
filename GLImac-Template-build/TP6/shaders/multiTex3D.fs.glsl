#version 330 core

in vec2 vTexCoords;
uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

out vec3 fFragColor;

void main() {
	fFragColor = (texture(uEarthTexture, vTexCoords)).xyz + (texture(uCloudTexture, vTexCoords)).xyz;
};