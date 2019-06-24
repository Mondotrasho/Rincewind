#ifndef CAMERA_H
#define CAMERA_H


#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

float delay = 0.1f;

class Camera {
private:	
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	glm::mat4 projection{};
	glm::mat4 view{};

	GLFWwindow* window;


public:

	Camera(GLFWwindow* w, float speed) : window(w),m_speed(speed), position(),front(glm::vec3(0.0f, 0.0f, -1.0f)),up(glm::vec3(0.0f, 1.0f, 0.0f))
	{
		updateView();
	}

	float m_speed;

	void setPerspective( float aspect, float fov = 75.0f, float n = 0.1f , float f = 1000.0f)
	{
		projection = glm::perspective(fov, aspect, n, f);
	};

	void updateView();
	const glm::mat4 getProjection_X_ViewMatrix();	
	void setPosition(glm::vec3 newpos);
	const glm::vec3 getPosition();
	void setFront(glm::vec3 newfront);
	const glm::vec3 getFront();
	const glm::vec3 getUp();

	const glm::mat4 getProjection();
	const glm::mat4 getView();

	void Input(float deltaTime);
	void update(float deltaTime);
};


//setters and getters

///SIMPLE

inline void Camera::setPosition(glm::vec3 newpos)
{
	position = newpos;
}

inline const glm::vec3 Camera::getPosition()
{
	return position;
}

inline void Camera::setFront(glm::vec3 newfront)
{
	front = newfront;
}

inline const glm::vec3 Camera::getFront()
{
	return front;
}

inline const glm::vec3 Camera::getUp()
{
	return up;
}

inline const glm::mat4 Camera::getProjection()
{
	return projection;
}

inline const glm::mat4 Camera::getView()
{
	return view;
}

///COMPLEX

inline void Camera::updateView()
{
	view = glm::lookAt(position, position + front, up);
}

inline const glm::mat4 Camera::getProjection_X_ViewMatrix()
{
	return projection * view;
}

//Input
//this is out input

inline void Camera::Input(float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	float cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraSpeed = 5.0f * deltaTime;
	else
		cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += cameraSpeed * front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= cameraSpeed * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(front, up)) * cameraSpeed;
	//Y
	//toggle polygonmode between wire frame and filled
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && delay <= 0)
	{
		position.y += cameraSpeed * 8 * deltaTime;
	}
	//toggle polygonmode between wire frame and filled
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && delay <= 0)
	{
		position.y -= cameraSpeed * 8 * deltaTime;
	}


	//toggle polygonmode between wire frame and filled
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && delay <= 0)
	{
		GLint polygonMode;
		glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
		if (polygonMode == GL_LINE)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		delay = 0.1f;
	}
	if (delay > 0)
		delay -= deltaTime;
}

inline void Camera::update(float deltaTime)
{
	Input(deltaTime);

	updateView();
}
#endif
