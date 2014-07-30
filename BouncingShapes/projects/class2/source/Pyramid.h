#ifndef PYRAMID_H
#define PYRAMID_H
#include "GLFrame/GLFrame.hpp"

class Pyramid
{
public:
	Pyramid();
	~Pyramid();
	GLfloat mShape[54];
	GLfloat pColours[54];
	void Translate(int x, int y, int z);
	void rotate();
	glm::vec4 getCenter();
	float getRadius();
	glm::vec4 trueCenter;
};


#endif