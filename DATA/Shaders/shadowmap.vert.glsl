#version 400 core

layout(location = 0) in vec4 vPosition;

uniform mat4 depthMVP;

void main()
{
	gl_Position = depthMVP * vPosition;
}

