#include "GLFrame/GLFrame.hpp"
#include "Pyramid.h"
#include <vector>
#include <math.h>
#include<random>
#include <time.h>
Pyramid::Pyramid()
{
	

	GLfloat pyramid[] = {
		// Triangle 1 Bottom
		0.0f, -4.0f, 0.0f,
		1.0f, -4.0f, 0.0f,
		0.0f, -4.0f, 1.0f,
		
		1.0f, -4.0f, 1.0f,
		0.0f, -4.0f, 1.0f,
		1.0f, -4.0f, 0.0f,

		//Front Face
		0.5f, -3.0, 0.5f,
		0.0, -4.0, 1.0f,
		1.0f, -4.0f, 1.0f,
		
		//Right Face
		0.5f, -3.0f, 0.5f,
		1.0f, -4.0f, 1.0f,
		1.0f, -4.0f, 0.0f,

		//Back Face

		0.5f, -3.0f, 0.5f,
		1.0f, -4.0f, 0.0f,
		0.0f, -4.0f, 0.0f,

		// Left Face

		0.5f, -3.0f, 0.5f,
		0.0f, -4.0f, 0.0f,
		0.0f, -4.0f, 1.0f,
	};

	GLfloat colours[] = {
		
		// Pyramid 1
		1.0f, 0.1f, 0.2f, // Floor 1
		1.0f, 0.1f, 0.2f,
		1.0f, 0.1f, 0.2f,

		1.0f, 0.1f, 0.2f, // Floor 2
		1.0f, 0.1f, 0.2f,
		1.0f, 0.1f, 0.2f,

		0.1f, 1.0f, 0.1f,// Back
		0.1f, 1.0f, 0.1f,
		0.1f, 1.0f, 0.1f,

		0.1f, 0.2f, 0.3f, // Left
		0.1f, 0.2f, 0.3f,
		0.1f, 0.2f, 0.3f,

		1.0f, 0.5f, 0.5f, // Right
		1.0f, 0.5f, 0.5f,
		1.0f, 0.5f, 0.5f,

		0.0f, 1.0f, 0.5f, // Front
		0.0f, 1.0f, 0.5f,
		0.0f, 1.0f, 0.5f
	};

	memcpy(mShape, pyramid, sizeof(pyramid));
	memcpy(pColours,colours,sizeof(colours));

	// Determine the center of the object

	trueCenter = glm::vec4(0.5f,  -3.5f, 0.5f, 1.0f);	
	

}


/*
 * Translate the Pyramid along the defined axis x, y, z
 * distance.
 * 
 * @params x y z The distance and axis to move along.
 */
void Pyramid::Translate(int x, int y, int z)
{
	// Translation matrix for pyramids.
	glm::mat4 pirTransMatrix = glm::mat4();
	pirTransMatrix = glm::translate(pirTransMatrix, glm::vec3(x, y, z));
	
	//Translate center
	glm::vec4 translateCenter = pirTransMatrix*trueCenter;
	trueCenter[0] = translateCenter[0];
	trueCenter[1] = translateCenter[1];
	trueCenter[2] = translateCenter[2];

	//Move the pyramid
	for(int i = 0; i < sizeof(mShape) / sizeof(GLfloat); i+=3){
			glm::vec4 vector = glm::vec4(mShape[i], mShape[i+1], mShape[i+2], 1.0f);
			glm::vec4 translate = pirTransMatrix*vector;
			mShape[i] = translate[0];
			mShape[i+1] = translate[1];
			mShape[i+2] = translate[2];
	}
}

/*
 * Depreciated function, this function rotated the pyramid to check all
 * sides were rendering correctly.
 */
void Pyramid::rotate()
{
	// matrix to rotate the vertices
	glm::mat4 piramidMatrix = glm::mat4(); // identity matrix 
	piramidMatrix = glm::rotate(piramidMatrix, 0.2f, glm::vec3(0, 1, 0));

	for(int i = 0; i < sizeof(mShape)/ sizeof (GLfloat); i+=3){
			glm::vec4 vector = glm::vec4(mShape[i], mShape[i+1], mShape[i+2], 1.0f);
			glm::vec4 rotate = piramidMatrix*vector;
			mShape[i] = rotate[0];
			mShape[i+1] = rotate[1];
			mShape[i+2] = rotate[2];
		}

}

/*
 * Return the center of the pyramid.
 */
glm::vec4 Pyramid::getCenter()
{
	return trueCenter;
}

/*
 * For bounding sphere collision, get the radius of
 * a sphere surrounding the pyramid.
 */
float Pyramid::getRadius()
{
	float xd = mShape[0] - trueCenter.x;
	float yd = mShape[1] - trueCenter.y;
	float zd = mShape[2] - trueCenter.z;
	

	
	float radius = sqrt(xd *xd + yd*yd + zd*zd);
	return radius -0.4;
}

Pyramid::~Pyramid(){} // Destructor.
