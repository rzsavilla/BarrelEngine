#version 430

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColour;

in vec4 vertPosition;

uniform mat4 mTranslate;
uniform mat4 mRotate;
uniform mat4 mScale;
uniform mat4 mOrigin;
uniform mat4 mOriginMinus;

uniform mat4 mView;
uniform mat4 mProjection;

in vec3 vertColour;
out vec3 Colour;

void main()
{
    Colour = vertColour;

    gl_Position = mProjection * mView * mTranslate * mOriginMinus * mRotate * mOrigin * mScale * vertPosition;
}
