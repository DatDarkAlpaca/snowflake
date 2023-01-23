#include "pch.h"
#include "SnowWindow.h"

namespace snow
{
	void SnowWindow::SnowWindowDeleter::operator()(GLFWwindow* window)
	{
		glfwDestroyWindow(window);
	}

	SnowWindow::SnowWindow(int width, int height, const char* title)
	{
		m_Window = std::unique_ptr<GLFWwindow, SnowWindowDeleter>(glfwCreateWindow(width, height, title, nullptr, nullptr), SnowWindowDeleter());

		if (!m_Window.get())
		{
			SNOW_LOG_ERROR("Failed to instantiate a GLFW window.");
			glfwTerminate();
		}
	}
}
