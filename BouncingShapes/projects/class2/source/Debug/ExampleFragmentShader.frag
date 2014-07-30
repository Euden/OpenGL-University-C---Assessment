#version 330 core

// Ouput data
out vec3 colour;
in vec3 fragmentColour;

void main()
{
	colour = fragmentColour;
}
