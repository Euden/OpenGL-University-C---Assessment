#include "GLFrame/GLFrame.hpp"
#include "ControlHandler.hpp"
#include "Pyramid.h"
#include "Cube.h"
#include <vector>
#include <random>
#include <time.h>

int main()
{
	// Initial OpenGL Setup using given framework.
	GLFrame &glFrame = GLFrame::getInstance();
	ControlHandler controlHandler;

	glFrame.glfwInit();
	glFrame.glfwMakeContextCurrent();
	glFrame.glfwSetKeyCallback();
	glFrame.glewInit();	

	GLuint vertexArrayID = glFrame.generateVAO();

	GLuint programmeID = glFrame.loadShaders("ExampleVertexShader.vert", "ExampleFragmentShader.frag");
	
	srand (static_cast <unsigned> (time(0)));		// Seed the random generator.

	// Create Pyramids
	Pyramid p1;	
	p1.Translate(rand() % 4 + (-4), 0, rand() % 4 + (-4));
	Pyramid p2;
	p2.Translate(rand() % 4, 0, rand() % 4 + (-4));
	Pyramid p3;
	p3.Translate(rand() % 4 + (-4), 0, rand() % 4);
	Pyramid p4;
	p4.Translate(rand() % 4, 0, rand() % 4);

	
	// Create the Cubes and translate them to a random position.
	
	Cube c1;
	c1.Translate((rand() % 4 + (-4)), (rand() % 4 + (-4)), (rand() % 4 + (-4)));
	
	Cube c2;
	c2.Translate((rand() % 4 + (-4)), (rand() % 4 + (-4)), (rand() % 4 + (-4)));

	Cube c3;
	c3.Translate((rand() % 4 + (-4)), (rand() % 4 + (-4)), (rand() % 4 + (-4)));
	
	

	int vertexCount = sizeof(p1.mShape) + sizeof(p2.mShape) + sizeof(p3.mShape) + sizeof(p4.mShape)
					+ sizeof(c1.mShape) + sizeof(c2.mShape) + sizeof(c3.mShape) /sizeof(GLfloat);
	
	
	GLuint vertexBufferID = glFrame.generateVBO();
	
	// Set up the buffer with our vertices.

	glBufferData(GL_ARRAY_BUFFER, sizeof(p1.mShape) + sizeof(p2.mShape) + sizeof(p3.mShape) + sizeof(p4.mShape) 
								+ sizeof(c1.mShape) + sizeof(c2.mShape) + sizeof(c3.mShape), NULL, GL_STATIC_DRAW); // Give our vertices to OpenGL.
	
	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glVertexAttribPointer(
		  0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		  3,                  // size
		  GL_FLOAT,           // type
		  GL_FALSE,           // normalized?
		  0,                  // stride
		  (GLvoid*)0          // array buffer offset
	);

	GLuint colourBufferID = glFrame.generateVBO();		// Set up the colour buffer.

	glBufferData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours) + sizeof(p4.pColours)
		+ sizeof(c1.cColours) + sizeof(c2.cColours) + sizeof(c3.cColours), p1.pColours, GL_DYNAMIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(p1.pColours), p1.pColours);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours), sizeof(p2.pColours), p2.pColours);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours), sizeof(p3.pColours), p3.pColours);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours), sizeof(p4.pColours), p4.pColours);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours)+ sizeof(p4.pColours), sizeof(c1.cColours), c1.cColours);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours) + sizeof(p4.pColours) + sizeof(c1.c1Colours), sizeof(c2.cColours), c2.cColours);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours) + sizeof(p4.pColours) + sizeof(c1.c1Colours) + sizeof(c2.cColours), sizeof(c3.cColours), c3.cColours);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(GLvoid*)0
	);


	glClearColor(0.4f,0.4f,0.4f,0.4f);

	glUseProgram(programmeID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	int width, height; // Used to track the screen.

	GLfloat pos = 0.01f;

	glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
	
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(p1.mShape), p1.mShape);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.mShape), sizeof(p2.mShape), p2.mShape);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.mShape) + sizeof(p2.mShape), sizeof(p3.mShape), p3.mShape);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.mShape) + sizeof(p2.mShape) + sizeof(p3.mShape), sizeof(p4.mShape), p4.mShape);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.mShape) + sizeof(p2.mShape) + sizeof(p3.mShape)+ sizeof(p4.mShape), sizeof(c1.mShape), c1.mShape);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.mShape) + sizeof(p2.mShape) + sizeof(p3.mShape) + sizeof(p4.mShape) + sizeof(c1.mShape), sizeof(c2.mShape), c2.mShape);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.mShape) + sizeof(p2.mShape) + sizeof(p3.mShape) + sizeof(p4.mShape) + sizeof(c1.mShape) + sizeof(c2.mShape), sizeof(c3.mShape), c3.mShape);
	
	

	while(!glFrame.glfwWindowShouldClose())
	{
		
		c1.move();
		c2.move();
		c3.move();
		
		// Collision Check Cube or pyramid
		if(c1.checkCollision(c2) || c1.checkCollision(c3) || c1.checkCollisionPir(p1) || c1.checkCollisionPir(p2) || c1.checkCollisionPir(p3) || c1.checkCollisionPir(p4))
		{
			
			glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours)+ sizeof(p4.pColours), sizeof(c1.ccColours), c1.ccColours);
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours)+ sizeof(p4.pColours), sizeof(c1.cColours), c1.cColours);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours) + sizeof(p4.pColours) + sizeof(c1.cColours), sizeof(c2.cColours), c2.cColours);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours) + sizeof(p4.pColours) + sizeof(c1.cColours) + sizeof(c2.cColours), sizeof(c3.cColours), c3.cColours);

		}
		

		if(c2.checkCollision(c3) || c2.checkCollision(c1) || c2.checkCollisionPir(p1) || c2.checkCollisionPir(p2) || c2.checkCollisionPir(p3) || c2.checkCollisionPir(p4))
		{
			glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours) + sizeof(p4.pColours) + sizeof(c1.cColours), sizeof(c2.ccColours), c2.ccColours);
		}
		
		
		if(c3.checkCollision(c1) || c3.checkCollision(c2)|| c3.checkCollisionPir(p1) || c3.checkCollisionPir(p2) || c3.checkCollisionPir(p3) || c3.checkCollisionPir(p4))
		{
			glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.pColours) + sizeof(p2.pColours) + sizeof(p3.pColours) + sizeof(p4.pColours) + sizeof(c1.cColours) + sizeof(c2.cColours), sizeof(c3.ccColours), c3.ccColours);

		}
		

		
		// replace vertices in the VBO
		glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.mShape) + sizeof(p2.mShape) + sizeof(p3.mShape) + sizeof(p4.mShape), sizeof(c1.mShape), c1.mShape);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.mShape) + sizeof(p2.mShape) + sizeof(p3.mShape) + sizeof(p4.mShape) + sizeof(c1.mShape), sizeof(c2.mShape), c2.mShape);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(p1.mShape) + sizeof(p2.mShape) + sizeof(p3.mShape) + sizeof(p4.mShape) + sizeof(c1.mShape) + sizeof(c2.mShape), sizeof(c3.mShape), c3.mShape);

		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		glFrame.glfwGetFramebufferSize(&width, &height);
		glViewport(0, 0, width, height);

		controlHandler.computeMatricesFromInputs();
		glm::mat4 const & view = controlHandler.getViewMatrix();
		glm::mat4 const & projection = controlHandler.getProjectionMatrix();

		glm::mat4 model = glm::mat4(1.0f);

		glm::mat4 MVP = projection * view * model;

		GLuint MatrixID = glGetUniformLocation(programmeID, "MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// draw the shapes
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		

		glFrame.glfwSwapBuffers();
		glFrame.glfwPollEvents();
	}

	
	glFrame.glfwDestroyWindow();

	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &colourBufferID);
	glDeleteVertexArrays(1, &vertexArrayID);
	
	glFrame.glfwTerminate();

	exit(EXIT_SUCCESS);
}

void key_callback(GLFrame &glFrame, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glFrame.glfwSetWindowShouldClose(GL_TRUE);
}