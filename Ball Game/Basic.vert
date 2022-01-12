// GLSL 3.3
#version 330

// Uniforms
uniform mat4 uWorldTransform;
uniform mat4 uViewTransform;

// Vertex attributes
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;

out vec2 fragTexCoord;

void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * uWorldTransform * uViewTransform;
	fragTexCoord = inTexCoord;
}