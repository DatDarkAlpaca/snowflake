#include "pch.h"
#include "SnowflakeApp.h"

#include "Logger.h"

namespace snow
{
	static void initializeGLFW()
	{
		if (glfwInit() != GLFW_TRUE)
		{
			SNOW_LOG_CRITICAL("The application could not initialize GLFW.");
			return;
		}

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		glfwSetErrorCallback(GLFWErrorCallback);
	}
}

namespace snow
{
	SnowflakeApp::SnowflakeApp(int width, int height, const char* title)
	{
		initializeLogger();

		initializeGLFW();

		m_Window = new SnowWindow(width, height, title);
	}

	SnowflakeApp::~SnowflakeApp()
	{
		delete m_Window;

		glfwTerminate();
	}

	void SnowflakeApp::run()
	{
		while (!glfwWindowShouldClose(m_Window->get()))
		{
			glfwPollEvents();
		}
	}
}

