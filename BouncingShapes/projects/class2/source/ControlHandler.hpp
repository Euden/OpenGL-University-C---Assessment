#ifndef __CONTROLHANDLER__
#define __CONTROLHANDLER__

	#include "GLFrame/GLFrame.hpp"

	static float g_PI = 3.14f;
	static float g_TAU = g_PI * 2;

	class ControlHandler
	{
		public:
			/**
			 * The Constructor for ControlHandler. It sets up most of the variables.
			 */
			ControlHandler() :
				m_glFrame(GLFrame::getInstance()),
				m_position(glm::vec3(0.f, 0.f, 14.f)),
				m_horizontalAngle(g_PI), // Facing toward -Z
				m_verticalAngle(0.f),
				m_initialFoV(45.f),
				m_speed(6.f),
				m_mouseSpeed(0.3f)
			{}

			/** 
			 * Computes the View and Projection Matrices.
			 */
			void computeMatricesFromInputs();

			/**
			 * Returns a reference to the View Matrix.
			 * @return A reference to the View Matrix.
			 */
			glm::mat4 const & getViewMatrix() { return m_viewMatrix; }
			
			/**
			 * Returns a reference to the Projection Matrix.
			 * @return A reference to the Projection Matrix.
			 */
			glm::mat4 const & getProjectionMatrix() { return m_projectionMatrix; }
		private:
			// GL Frame Pointer //
			GLFrame &m_glFrame;
			//////////////////////
			// Matrices //
			glm::mat4 m_viewMatrix;
			glm::mat4 m_projectionMatrix;
			glm::vec3 m_position;
			//////////////
			// Members //
			float m_horizontalAngle;
			float m_verticalAngle;
			float m_initialFoV;
			float m_speed;
			float m_mouseSpeed;
			/////////////
	};
#endif //__CONTROLHANDLER__