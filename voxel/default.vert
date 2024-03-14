#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;

uniform mat4 cameramatrix;

out vec4 Color;

void main()
{
	gl_Position = cameramatrix * vec4(vPosition, 1.0);
	Color = vColor;
}