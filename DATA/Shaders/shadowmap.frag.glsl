#version 450 core

//layout(location = 0) out float fDepth;
out vec4 outColor;

void main()
{
	outColor = vec4(1.0);
	//fDepth = gl_FragCoord.z;
}
