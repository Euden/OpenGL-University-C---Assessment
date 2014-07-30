
#ifndef CUBE_H
#define CUBE_H
#include "GLFrame/GLFrame.hpp"
#include "Pyramid.h"
class Cube
{
public:
	Cube();
	~Cube();
	GLfloat mShape[108];
	GLfloat cColours[108];
	GLfloat ccColours[108];
	GLfloat c1Colours[108];
	void move();
	void Translate(int x, int y, int z);
	bool checkCollision(Cube c);
	bool checkCollisionPir(Pyramid p);
	glm::vec4 getCenter();
	float getRadius();
	glm::vec4 center;
	
private:
	double xVol, yVol, zVol, random;
	float radius;
	glm::vec3 velocity;
};


#endif