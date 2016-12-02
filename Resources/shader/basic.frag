#version 430

uniform sampler2D tex;
in vec2 texCoord;
in vec3 Colour;

out vec4 FragColour;

void main() {

    FragColour = vec4(Colour, 1.0);
	//FragColour = texture(tex,texCoord);
}