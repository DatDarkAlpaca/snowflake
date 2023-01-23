#include "pch.h"
#include "SnowflakeApp.h"

#include "Logger.h"

// Todo: implement an abstraction
#include "platform/vulkan/VulkanInstance.h"
#include "platform/vulkan/VulkanMessenger.h"
#include "platform/vulkan/VulkanDevice.h"

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
	SnowflakeApp::SnowflakeApp(int width, int height, const char* title, const char* applicationName)
	{
		initializeLogger();

		initializeGLFW();

		m_Window = new SnowWindow(width, height, title);

		m_VulkanInstance = vulkan::createInstance(applicationName, "Snowflake Engine");

#ifdef SNOW_DEBUG
		m_Dispatcher = vk::DispatchLoaderDynamic(m_VulkanInstance, vkGetInstanceProcAddr);
		m_DebugMessenger = vulkan::createDebugMessenger(m_VulkanInstance, m_Dispatcher);
#endif

		m_PhysicalDevice = vulkan::selectPhysicalDevice(m_VulkanInstance);
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

