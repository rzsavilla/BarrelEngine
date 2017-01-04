#version 430

uniform sampler2D tex;
in vec2 texCoord;
in vec3 Colour;

out vec4 colour;

void main() {
	colour = texture(tex,texCoord);
}