#version 400 core

layout(location = 0) in vec4 vPosition;
out vec2 uvs;

uniform mat4 Model;

void main()
{
	gl_Position = Model * vPosition;
	uvs = vec2((vPosition.x+1.0)/2.0, 1 - (vPosition.y+1.0)/2.0);
}

