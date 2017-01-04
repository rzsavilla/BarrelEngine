#version 430

layout (location=0) in vec3 VertexPosition;

in vec4 vertPosition;

uniform mat4 mTranslate;
uniform mat4 mRotate;
uniform mat4 mScale;
uniform mat4 mOrigin;
uniform mat4 mOriginMinus;

uniform mat4 mView;
uniform mat4 mProjection;

void main()
{
    //Colour = myColour;
    gl_Position = mProjection * mView * mTranslate * mOrigin * mOriginMinus * mRotate * mOrigin * mScale * vec4(VertexPosition,1.0);
}
