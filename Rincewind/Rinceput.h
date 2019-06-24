#pragma once
#include <GLFW/glfw3.h>

class Rinceput
{
public:
	Rinceput();
	~Rinceput();

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window);

	bool Rinceput::isKeyDown(int inputKeyID) {
		return m_currentKeys[inputKeyID] == GLFW_PRESS;
	}

	bool Rinceput::isKeyUp(int inputKeyID) {
		return m_currentKeys[inputKeyID] == GLFW_RELEASE;
	}

	bool Rinceput::wasKeyPressed(int inputKeyID) {
		return m_currentKeys[inputKeyID] == GLFW_PRESS &&
			m_lastKeys[inputKeyID] == GLFW_RELEASE;
	}
};

