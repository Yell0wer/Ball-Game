// GLSL 3.3
#version 330

in vec2 fragTexCoord;
// Output color for color buffer
out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
	outColor = texture(uTexture, fragTexCoord);
}