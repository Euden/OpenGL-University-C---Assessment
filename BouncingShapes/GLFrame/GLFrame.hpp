#ifndef __GLFRAME__
#define __GLFRAME__

	#ifdef WIN32
	#undef APIENTRY // This is to stop Windows from complaining about APIENTRY already being defined.
	#endif

	// These are here to make GLFW expose the right functionality //
	#ifdef WIN32
	#define GLFW_EXPOSE_NATIVE_WIN32
	#define GLFW_EXPOSE_NATIVE_WGL
	#elif defined(MACOSX)
	#define GLFW_EXPOSE_NATIVE_COCOA
	#define GLFW_EXPOSE_NATIVE_NSGL
	#elif defined(__unix)
	#define GLFW_EXPOSE_NATIVE_X11
	#define GLFW_EXPOSE_NATIVE_GLX
	#endif
	////////////////////////////////////////////////////////////////

	// Include GLEW //
	#include "glew/include/GL/glew.h"
	//////////////////

	// Include standard headers needed by GLFrame //
	#include <stdio.h>
	#include <stdlib.h>
	#include <fstream>
	#include <string>
	#include <cstring>
	#include <iostream>
	////////////////////////////////////////////////

	// Include GLFW //
	#include "glfw/include/GLFW/glfw3.h"
	#ifdef WIN32
	#undef APIENTRY // This is to stop Windows from complaining about APIENTRY already being defined.
	#endif
	#include "glfw/include/GLFW/glfw3native.h"
	//////////////////

	// Include GLM //
	#include "glm/glm.hpp"
	#include "glm/gtx/transform.hpp"
	#include "glm/gtc/matrix_transform.hpp"
	/////////////////

	/**
	 * An Enum which stores the current status of the GLFrame instance.
	 *
 	 * NONE means that GLFrame is in its initial state and needs initialising.
	 * GLFW means that GLFW has been started but not bound to yet.
	 * BOUND means that GLFW has been started and bound to, but glew still needs to be loaded.
	 * FULL means that GLFrame is fully initialised and ready to be used.
	 */
	enum GLFrameStatus { NONE, GLFW, BOUND, FULL }; // This is used to check the status of GLFrame.

	/**
	 * @file
	 * @author Jack Blower <jlgb4@kent.ac.uk>
	 * @version 2.1
	 * 
	 * @section DESCRIPTION
	 * GLFrame is a simple GLFW wrapper framework that provides a working environment for OpenGL
	 * by using the GLFW Window Handler framework.
	 */
	
	 /** 
	 * GLFrame tries to abstract away the raw window as much as possible which makes code slightly cleaner
	 * than normal OpenGL code, it also provides shader loading code and a mouse function which can get the
	 * mouse coördinates wherever your mouse is on the screen.
	 * The mouse function that gets your coördinates outside the context has not been implemented for Mac.
	 */
	class GLFrame
	{
		public:
			/**
			 * Initialises the GLFW Window handler and opens a window with OpenGL 3.3 and 4 samples.
			 * 
			 * @param windowTitle The title of the window to be opened.
			 */
			void glfwInit(std::string windowTitle);

			/**
			 * Makes the context the current context. Must be called after glfwInit and before glewInit.
			 */
			void glfwMakeContextCurrent();

			/**
			 * Asks GLFW if the window should close.
			 * 
			 * @return True if the window should close.
			 */
			bool glfwWindowShouldClose()  { return ::glfwWindowShouldClose(m_window) != 0; }

			/**
			 * Destroys the window.
			 */
			void glfwDestroyWindow() { ::glfwDestroyWindow(m_window); }

			/**
			 * Terminates GLFW
			 */
			void glfwTerminate() { ::glfwTerminate(); }

			/**
			 * Tells GLFW if the window should close or not.
			 *
			 * @param value Whether the window should close or not. Should be GL_TRUE for close.
			 */
			void glfwSetWindowShouldClose(GLint value) { ::glfwSetWindowShouldClose(m_window, value); }

			/**
			 * Sets the key callback to the function that should be defined in your main.cpp
			 */
			void glfwSetKeyCallback();

			/**
			 * Swaps the buffers over. GLFW is doubled buffered so this should be swapped once per iteration.
			 */
			void glfwSwapBuffers() { ::glfwSwapBuffers(m_window); }

			/**
			 * Polls GLFW for any events.
			 */
			void glfwPollEvents() { ::glfwPollEvents(); }
			
			/**
			 * Returns the context size.
			 *
			 * @param width A pointer to hold the width of the context in pixels.
			 * @param height A pointer to hold the height of the context in pixels.
			 */
			void glfwGetFramebufferSize(int *width, int *height) { ::glfwGetFramebufferSize(m_window, width, height); }

			/**
			 * Initialises glew to make sure the 3.3 functionality is available for use.
			 */
			void glewInit();

			/**
			 * Generates and binds to a Vertex Array Object for managing VBOs.
			 * 
			 * @return The ID of the created VAO.
			 */
			GLuint generateVAO();

			/**
			 * Generates and binds to a Vertex Buffer Object.
			 * 
			 * @return The ID of the created VBO
			 */
			GLuint generateVBO();

			/**
			 * Generates and binds to an index buffer array for the current VAO.
			 * 
			 * @return The ID of the created index buffer array.
			 */
			GLuint generateIndexBuffer();
			
			// These methods are located in GLFrameShader.cpp //
			/**
			 * Opens a file and returns its contents.
			 * Warning this method could add a \n to the returned file.
			 *
			 * @param filename The filename to open and return. (May contain a path)
			 * 
			 * @return The contents of filename.
			 */
			char const * const getFileContents(char const *filename);

			/**
			 * Loads two shaders from two filenames and returns the ID of the compiled programme if they compiled correctly.
			 * The programme will exit without a Vertex Shader, to try an teach proper OpenGL 3.3 practises.
			 *
			 * @param vertexShaderFilename The file name (and possibly path) to open and load as a vertex shader.
			 * @param fragmentShaderFilename The file name (and possibly path) to open and load as a fragment shader.
			 * 
			 * @return The shader programme ID.
			 */
			GLuint loadShaders(char const * vertexShaderFilename, char const * fragmentShaderFilename);
			////////////////////////////////////////////////////

			// The definition for getMouseRelPostition is located in GLFrameMouse.cpp //
			// These functions do NOT work on Mac.                                    //
			/**
			 * Gets the current mouse position relative to the overall display.
			 * Note: This function can track the mouse anywhere on the screen, unlike the GLFW mouse function which is bound to the conext.
			 *
			 * @param xPos A pointer which will hold the current x position.
			 * @param yPos A pointer which will hold the current y position.
			 */
			void getMouseDispRelPosition(int *xPos, int *yPos) const { getMouseRelPosition(xPos, yPos, false); }

			/**
			 * Gets the current mouse position relative to the GLFW window.
			 * Note: This function can track the mouse anywhere on the screen, unlike the GLFW mouse function which is bound to the conext.
			 *
			 * @param xPos A pointer which will hold the current x position.
			 * @param yPos A pointer which will hold the current y position.
			 */
			void getMouseWindRelPosition(int *xPos, int *yPos) const { getMouseRelPosition(xPos, yPos, true); }
			////////////////////////////////////////////////////////////////////////////

			/**
			 * Prints an error message and exits the application with EXIT_FAILURE.
			 *
			 * @param errorString The error message to print before exiting.
			 */
			void printErrorAndExit( char const * const errorString ) const;

			/**
			 * Returns the singleton instance of GLFrame
			 *
			 * @return The GLFrame singleton instance.
			 */
			static GLFrame &getInstance() { return *GLFrame::glFrame; }

			/**
			 * Initialises the GLFW Window handler and opens a window with OpenGL 3.3 and 4 samples with the window title "GLFrame".
			 */
			void glfwInit() { glfwInit("GLFrame"); }

			/**
			 * Gets the cursor position relative to the context boundaries with 0,0 being top left.
			 * Note: This function *only* works while inside the context bounds.
			 *
			 * @param xPos A pointer which will contain the current x position of the mouse.
			 * @param yPos A pointer which will contain the current y position of the mouse.
			 */
			void glfwGetCursorPos(double *xPos, double *yPos) const { ::glfwGetCursorPos(m_window, xPos, yPos); }

			/**
			 * Sets the cursor position relative to the top left boundary of the context window.
			 * Note: Only works if the cursor is inside the context bounds and 
			 *
			 * @param xPos A reference to an x position for the cursor to be set to.
			 * @param yPos A reference to an y position for the cursor to be set to.
			 */
			void glfwSetCursorPos(const double &xPos, const double &yPos) { ::glfwSetCursorPos(m_window, xPos, yPos); }

			/**
			 * Returns the current X Mousewheel Offset.
			 *
			 * @return The current X Mousewheel Offset.
			 */
			const double getMouseWheelX() const { return m_xScrollOffset; }
			
			/**
			 * Returns the current Y Mousewheel Offset.
			 *
			 * @return The current Y Mousewheel Offset.
			 */
			const double getMouseWheelY() const { return m_yScrollOffset; }

			/**
			 * Returns the status of a key since the last time it was checked.
			 *
			 * @param key The key . Look at http://www.glfw.org/docs/latest/group__keys.html for all the keys.
			 * 
			 * @return An int whether the key is pressed or released.
			 */
			int const glfwGetKey(int key) const { return ::glfwGetKey(m_window, key); }

			/**
			 * Gets the current time offset according to GLFW.
			 * This starts from 0 when GLFW is initialised.
			 *
			 * @return The current time according to GLFW as a double.
			 */
			double glfwGetTime() const { return ::glfwGetTime(); }

			/**
			 * GLFrame destructor which makes sure GLFW destroys its window if open.
			 */
			~GLFrame() { glfwDestroyWindow(); }
		private:
			/**
			 * Constructor for GLFrame.
			 */
			GLFrame();
			
			/**
			 * Singleton GLFrame holder.
			 */
			static GLFrame * const glFrame;

			/**
			 * The current status of GLFrame in the programme.
			 */
			GLFrameStatus m_glFrameStatus;
			
			/**
			 * The GLFW callback for key presses.
			 */
			void static key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			
			/**
			 * The GLFW Window which is abstracted from students.
			 */
			GLFWwindow *m_window;

			/**
			 * The x scroll offset of the mouse.
			 */
			double m_xScrollOffset;

			/**
			 * The y scroll offset of the mouse.
			 */
			double m_yScrollOffset;

			/**
			 * This function is a callback for error events in GLFW. It prints the error to the stderr.
			 */
			void static error_callback(int error, char const * description) { fputs(description, stderr); }

			/**
			 * This function is a callback for the scroll event in GLFW. It adjusts the current scroll offsets.
			 *
			 * @param window The GLFW window that caused the event.
			 * @param xOffset The new X offset of the mousewheel.
			 * @param yOffset The new Y offset of the mousewheel.
			 */
			void static scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
			{
				GLFrame::getInstance().m_xScrollOffset += xOffset;
				GLFrame::getInstance().m_yScrollOffset += yOffset;
			}

			/**
			 * This function checks that GLFrame is fully initialised and if not it prints an error.
			 */
			void requireFullInit() const;

			// This function is located in GLFrameShader.cpp //
			/**
			 * Prints an error about shader compilation / loading and exits the application with EXIT_FAILURE.
			 *
			 * @param shaderType The type of shader, "Vertex" or "Fragment"
			 * @param shaderFilename The filename/path of the shader
			 */
			void printShaderErrorAndExit( char const * const shaderType, char const * const shaderFilename);
			///////////////////////////////////////////////////

			// This function is located in GLFrameMouse.cpp //
			/**
			 * Gets the current mouse position, either based on the screen or based on the top left of the window.
			 * Note: This function can track the mouse anywhere on the screen, unlike the GLFW mouse function which is bound to the context.
			 *
			 * @param xPos A pointer which will hold the current x position.
			 * @param yPos A pointer which will hold the current y position.
			 * @param winRel A boolean to decide whether the coördinates are based on window or the screen.
			 *
			 * This will NOT work on Mac.
			 */
			void getMouseRelPosition(int *xPos, int *yPos, bool winRel) const;
			///////////////////////////////////////////////////
	};
#endif //__GLFRAME__
