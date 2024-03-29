#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColour;

uniform mat4 MVP;

out vec3 fragmentColour;
 
void main()
{
    vec4 v = vec4(vertexPosition_modelspace,1);
    gl_Position = MVP * v;

	fragmentColour = vertexColour;
}