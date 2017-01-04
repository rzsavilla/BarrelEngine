#version 430

uniform vec3 myColour;
out vec4 Colour;

void main() {
	Colour = vec4(myColour,1.0);
}