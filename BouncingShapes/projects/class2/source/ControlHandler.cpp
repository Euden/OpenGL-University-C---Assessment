#include "ControlHandler.hpp"

void ControlHandler::computeMatricesFromInputs()
{
	// Call this the first time the method is ran, to set-up an initial time.
	static double lastTime = m_glFrame.glfwGetTime();

	// Compute the time differences between the current and the last frame
	double currentTime = m_glFrame.glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	//std::cout << deltaTime << "\n";

	double xPos, yPos;
	m_glFrame.glfwGetCursorPos(&xPos, &yPos);

	//std::cout << xPos << " : " << yPos << '\n';

	int xSize, ySize;
	m_glFrame.glfwGetFramebufferSize(&xSize, &ySize);
	double midX = double(xSize) / 2.0;
	double midY = double(ySize) / 2.0;

	//std::cout << midX << ":" << midY << '\n';

	m_glFrame.glfwSetCursorPos(midX, midY);

	// Compute the horizontal and vertical orientation //
	//m_horizontalAngle += float(m_mouseSpeed * deltaTime * (midX - xPos));
	//m_verticalAngle   += float(m_mouseSpeed * deltaTime * (midY - yPos));
	/////////////////////////////////////////////////////

	//std::cout << m_horizontalAngle << " : " << m_verticalAngle << '\n';

	if(m_horizontalAngle > g_TAU) m_horizontalAngle -= g_TAU;
	if(m_horizontalAngle < 0) m_horizontalAngle += g_TAU;

	if(m_verticalAngle > g_TAU) m_verticalAngle -= g_TAU;
	if(m_verticalAngle < 0) m_verticalAngle += g_TAU;

	//std::cout << m_horizontalAngle << ":" << m_verticalAngle << '\n';

	// Pre-calculate cos for vertical for a slight speed up //
	//float cosVert = glm::cos(m_verticalAngle);
	//////////////////////////////////////////////////////////

	glm::vec3 direction(
		glm::cos(m_verticalAngle) * glm::sin(m_horizontalAngle),
		glm::sin(m_verticalAngle),
		glm::cos(m_verticalAngle) * glm::cos(m_horizontalAngle)
	);


	glm::vec3 right = glm::vec3(
		glm::sin(m_horizontalAngle - g_PI/2.f),
		0,
		glm::cos(m_horizontalAngle - g_PI/2.f)
	);

	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	//if (m_glFrame.glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS) m_position += direction * deltaTime * m_speed;
	
	// Move backward
	//if (m_glFrame.glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS) m_position -= direction * deltaTime * m_speed;
	
	// Strafe right
	//if (m_glFrame.glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS) m_position += right * deltaTime * m_speed;
	
	// Strafe left
	//if (m_glFrame.glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS) m_position -= right * deltaTime * m_speed;

	float FoV = float(m_initialFoV - 5 * m_glFrame.getMouseWheelY());
	m_projectionMatrix = glm::perspective(FoV, float(xSize)/ySize, 0.1f, 100.f);

	m_viewMatrix = glm::lookAt(
		m_position,
		m_position + direction,
		up
	);

	lastTime = currentTime;
}
