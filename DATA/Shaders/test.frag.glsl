#version 450 core

//layout(location = 0) out float fDepth;
out vec4 outColor;
in vec2 uvs;

uniform sampler2D guiTexture;
uniform sampler2D tex2;

void main()
{
	//outColor = vec4(1.0);
	outColor = texture(guiTexture, uvs);
}
