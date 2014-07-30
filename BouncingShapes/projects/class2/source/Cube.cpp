#include "Cube.h"
#include "Pyramid.h"
#include <math.h>
#include <random>
#include <functional>
#include <time.h>

// Create the Cube.
Cube::Cube()
{
	 GLfloat cube[] = {
		 2.0f,  3.0f, -4.0f, // triangle 1, top right 
		 3.0f,  3.0f, -4.0f,
		 2.0f,  2.0f, -4.0f, // bottom right

		 3.0f,  3.0f, -4.0f, // triangle 2, back face top left
		 3.0f,  2.0f, -4.0f, // bottom left
		 2.0f,  2.0f, -4.0f,

		 2.0f,  3.0f, -3.0f, // triangle 1, front face top left // Center is: 2.5, 2.5, -2.5
		 2.0f,  2.0f, -3.0f, // bottom left
		 3.0f,  3.0f, -3.0f, // Bottom right

		 3.0f,  3.0f, -3.0f, // triangle 2, front face
		 2.0f,  2.0f, -3.0f,
		 3.0f,  2.0f, -3.0f, // Bottom right

		 2.0f,  3.0f, -3.0f, // triangle 1, top face
		 3.0f,  3.0f, -3.0f,
		 2.0f,  3.0f, -4.0f,
		 3.0f,  3.0f, -4.0f, // triangle 2, top face
		 2.0f,  3.0f, -4.0f,
		 3.0f,  3.0f, -3.0f,

		 2.0f,  2.0f, -3.0f, // triangle 1, bottom face
		 2.0f,  2.0f, -4.0f,
		 3.0f,  2.0f, -3.0f,
		 3.0f,  2.0f, -4.0f, // triangle 2, bottom face
		 3.0f,  2.0f, -3.0f, // Bottom Right.
		 2.0f,  2.0f, -4.0f,

		 2.0f,  2.0f, -4.0f, // triangle 1, left face
		 2.0f,  2.0f, -3.0f,
		 2.0f,  3.0f, -4.0f,
		 2.0f,  3.0f, -4.0f, // triangle 2, left face
		 2.0f,  2.0f, -3.0f,
		 2.0f,  3.0f, -3.0f,

		 3.0f,  2.0f, -4.0f, // triangle 1, right face
		 3.0f,  3.0f, -4.0f,
		 3.0f,  2.0f, -3.0f,
		 3.0f,  3.0f, -4.0f, // triangle 2, right face
		 3.0f,  3.0f, -3.0f,
		 3.0f,  2.0f, -3.0f,

	};

	 GLfloat colours[] = {
		1.0f, 1.0f, 0.0f, // Back 1 //top right
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, // Bottom Right

		1.0f, 1.0f, 0.0f, // Back 2 // Top left
		1.0f, 1.0f, 0.0f, // Bottom left
		1.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 1.0f, //Front 1 // Top left
		0.0f, 1.0f, 1.0f, // Bottom left
		0.0f, 1.0f, 1.0f, // top right

		0.0f, 1.0f, 1.0f, //Front 2
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, // Bottom Right
		
		1.0f, 0.5f, 1.0f, //Top 1 
		1.0f, 0.5f, 1.0f,
		1.0f, 0.5f, 1.0f,

		1.0f, 0.5f, 1.0f, //Top 2
		1.0f, 0.5f, 1.0f,
		1.0f, 0.5f, 1.0f,

		1.0f, 1.0f, 1.0f, // Bottom - White
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, // Bottom 
		1.0f, 1.0f, 1.0f, //Bottom Right
		1.0f, 1.0f, 1.0f,

		0.91f, 0.76f, 0.65f, // Left - Light wood
		0.91f, 0.76f, 0.65f,
		0.91f, 0.76f, 0.65f,

		0.91f, 0.76f, 0.65f, // Left - Light wood
		0.91f, 0.76f, 0.65f,
		0.91f, 0.76f, 0.65f,

		0.137255f, 0.137255f, 0.55686f, // Right - Navy blue
		0.137255f, 0.137255f, 0.55686f,
		0.137255f, 0.137255f, 0.55686f,

		0.137255f, 0.137255f, 0.55686f,
		0.137255f, 0.137255f, 0.55686f,
		0.137255f, 0.137255f, 0.55686f,
	 };

	 // Colours for when colliding with another Cube or Pyramid.
	 GLfloat coloursCol[] = {

		0.0f, 1.0f, 1.0f, //Front 1 // Top left
		0.0f, 1.0f, 1.0f, // Bottom left
		0.0f, 1.0f, 1.0f, // top right

		0.0f, 1.0f, 1.0f, //Front 2
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, // Bottom Right
		
		1.0f, 0.5f, 1.0f, //Top 1 
		1.0f, 0.5f, 1.0f,
		1.0f, 0.5f, 1.0f,

		1.0f, 0.5f, 1.0f, //Top 2
		1.0f, 0.5f, 1.0f,
		1.0f, 0.5f, 1.0f,

		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 

		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f,

		1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,  
		1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f, 1.0f,

		0.137255f, 0.137255f, 0.55686f, // left - Navy blue
		0.137255f, 0.137255f, 0.55686f,
		0.137255f, 0.137255f, 0.55686f,

		0.137255f, 0.137255f, 0.55686f,
		0.137255f, 0.137255f, 0.55686f,
		0.137255f, 0.137255f, 0.55686f,
		
		0.91f, 0.76f, 0.65f, // right - Light wood
		0.91f, 0.76f, 0.65f,
		0.91f, 0.76f, 0.65f,

		0.91f, 0.76f, 0.65f, // right - Light wood
		0.91f, 0.76f, 0.65f,
		0.91f, 0.76f, 0.65f,

		

		
	 };

	 // Copy these arrays to be used inside the main class.

	 memcpy(mShape, cube, sizeof(cube));		// Copy the memory to mShape to be used in the main class.
	 memcpy(cColours, colours, sizeof(colours));
	 memcpy(ccColours, coloursCol, sizeof(coloursCol));
	 

	 // Calculate initial center of the shape by finding the average of all the vertices.
	 glm::vec3 corner1 = glm::vec3(2.0f,  3.0f, -4.0f);
	 glm::vec3 corner2 = glm::vec3(2.0f,  2.0f, -4.0f);
	 glm::vec3 corner3 = glm::vec3(3.0f,  3.0f, -4.0f);
	 glm::vec3 corner4 = glm::vec3(3.0f,  2.0f, -4.0f);
	 glm::vec3 corner5 = glm::vec3(2.0f,  3.0f, -3.0f);
	 glm::vec3 corner6 = glm::vec3(2.0f,  2.0f, -3.0f);
	 glm::vec3 corner7 = glm::vec3(3.0f,  3.0f, -3.0f);
	 glm::vec3 corner8 = glm::vec3(3.0f,  2.0f, -3.0f);

	GLfloat x = (corner1.x + corner2.x + corner3.x + corner4.x + corner5.x + corner6.x+ corner7.x + corner8.x)/8;
	GLfloat y = (corner1.y + corner2.y + corner3.y + corner4.y + corner5.y + corner6.y+ corner7.y + corner8.y)/8;
	GLfloat z = (corner1.z + corner2.z + corner3.z + corner4.z + corner5.z + corner6.z+ corner7.z + corner8.z)/8;
	
	center = glm::vec4(x, y, z, 1.0f);
	
	 //Set up initial movement velocities
	  random = (double)rand() / RAND_MAX;
     
	 xVol = (-0.002 + random * (0.002 - (-0.002)));
	 random = (double)rand() / RAND_MAX;
	 yVol = (-0.002 + random * (0.002 - (-0.002)));
	 random = (double)rand() / RAND_MAX;
	 zVol = (-0.002 + random * (0.002 - (-0.002)));
	 
}


/*
 * Translate the cube to the given location.
 * @params x, y ,z The three points in which to translate to.
 */
void Cube::Translate(int x, int y, int z)
{
	// Translation matrix for cube.
	glm::mat4 cubeTransMatrix = glm::mat4();
	cubeTransMatrix = glm::translate(cubeTransMatrix, glm::vec3(x, y, z));
	
	glm::vec4 translateCenter = cubeTransMatrix*center;
	center[0] = translateCenter[0];
	center[1] = translateCenter[1];
	center[2] = translateCenter[2];
	
	//Move the cube
	for(int i = 0; i < sizeof(mShape) / sizeof(GLfloat); i+=3){
			glm::vec4 vector = glm::vec4(mShape[i], mShape[i+1], mShape[i+2], 1.0f);
			glm::vec4 translate = cubeTransMatrix*vector;
			mShape[i] = translate[0];
			mShape[i+1] = translate[1];
			mShape[i+2] = translate[2];
			
	}
}


/*
 * Translate the cube at the randomly defined velocity.
 * check to see if we are about to go out of bounds in each direction, if so,
 * reverse that directions velocity to simulate bouncing.
 *
 * Drag is applied to the velocities and will slow down the cubes eventually. (Experimental)
 */
void Cube::move()
{
	//Drag
	xVol -= 0.00000001f;
	yVol -= 0.00000001f;
	zVol -= 0.00000001f;
	
	// Translation matrix for cube.
	glm::mat4 cubeTransMatrix = glm::mat4();
	for(int x = 0; x < sizeof(mShape) / sizeof(GLfloat); x+=3)
	{
		if(mShape[x] <= -4.0f && xVol < 0)
		{
			xVol *=-1;
			
		}
		if(mShape[x] > 4.0f && xVol > 0)
		{
			xVol *= -1;
			
		}

		//Y bounds
		if(mShape[x+1] < -4.0f && yVol < 0)
		{
			yVol *= -1;
		}
		if(mShape[x+1] > 4.0f && yVol > 0)
		{
			yVol *= -1;
		}

		// Zbounds
		if(mShape[x+2] <= -4.0f && zVol < 0)
		{
			zVol *= -1;
		}
		if(mShape[x+2] > 4.0f && zVol > 0)
		{
			zVol *= -1;
		}
	}
	
	cubeTransMatrix = glm::translate(cubeTransMatrix, glm::vec3(xVol, yVol, zVol));
	glm::vec4 translateCenter = cubeTransMatrix*center;
	center[0] = translateCenter[0];
	center[1] = translateCenter[1];
	center[2] = translateCenter[2];
	
	//Move the cube
	for(int i = 0; i < sizeof(mShape) / sizeof(GLfloat); i+=3){
			glm::vec4 vector = glm::vec4(mShape[i], mShape[i+1], mShape[i+2], 1.0f);
			glm::vec4 translate = cubeTransMatrix*vector;
			glm::vec4 translateCenter = cubeTransMatrix*center;
			mShape[i] = translate[0];
			mShape[i+1] = translate[1];
			mShape[i+2] = translate[2];
	}


}

/*
 * Check to see if we are colliding with a cube.
 * If we are, return true. Otherwise return false.
 * Bounding sphere collision.
 * @param c The cube to check.
 */
bool Cube::checkCollision(Cube c)
{
	float r0sqr = getRadius() * getRadius();
	float r1sqr = c.getRadius() * c.getRadius();

	float distX = getCenter().x - c.getCenter().x;
	float distY = getCenter().y - c.getCenter().y;
	float distZ = getCenter().z - c.getCenter().z;

	// Since we already need to square these, we won't need to take the absolute value
	// to accurately compare them to the radii
	distX *= distX;
	distY *= distY;
	distZ *= distZ;

	float sqrDist = (distX+distY+distZ);

	if((r0sqr + r1sqr) > sqrDist - 0.5f)
	{
		return true;
	}
	
	 
	return false;
}

/*
 * Check for collisions with a pyramid. If we are return true
 * otherwise return false.
 */
bool Cube::checkCollisionPir(Pyramid p)
{
	float r0sqr = getRadius() * getRadius();
	float r1sqr = p.getRadius() * p.getRadius();

	float distX = getCenter().x - p.getCenter().x;
	float distY = getCenter().y - p.getCenter().y;
	float distZ = getCenter().z - p.getCenter().z;

	// Since we already need to square these, we won't need to take the absolute value
	// to accurately compare them to the radii
	distX *= distX;
	distY *= distY;
	distZ *= distZ;

	float sqrDist = (distX+distY+distZ);

	if((r0sqr + r1sqr) > sqrDist )
	{
		return true;
	}
	
	return false;
}

/*
 * Simply return the center of the cube.
 * @return center The center of the cube for use in collisions.
 */
glm::vec4 Cube::getCenter()
{
	return center;
}


/*
 * Get the radius of the cube by taking the 3 vertices of the corner
 * and getting the distance from the center.
 * square the answer to provide the radius.
 * @return radius The radius -0.1 as it is a sphere so to keep it just within the bounds of the cube.
 */
float Cube::getRadius()
{
	float xd = mShape[0] - center.x;
	float yd = mShape[1] - center.y;
	float zd = mShape[2] - center.z;
	

	
	radius = sqrt(xd *xd + yd*yd + zd*zd);
	return radius - 0.1;
}

Cube::~Cube()		// Destructor.
{
	
}