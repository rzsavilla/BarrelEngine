#version 430

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColour;

in vec4 vertPosition;

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;

in vec3 vertColour;
out vec3 Colour;

void main()
{
    Colour = vertColour;

    gl_Position = mProjection * mView * mModel * vertPosition;
}
