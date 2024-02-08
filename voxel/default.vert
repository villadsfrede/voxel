#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;

uniform mat4 cameramatrix;

void main()
{
	gl_Position = cameramatrix * vec4(aPos, 1.0);
}