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

		VkSurfaceKHR surface;
		if (glfwCreateWindowSurface(m_VulkanInstance, m_Window->get(), nullptr, &surface) != VK_SUCCESS)
		{
			SNOW_LOG_ERROR("Failed to abstract a GLFW window surface.");
			return;
		}
		m_Surface = surface;

#ifdef SNOW_DEBUG
		m_Dispatcher = vk::DispatchLoaderDynamic(m_VulkanInstance, vkGetInstanceProcAddr);
		m_DebugMessenger = vulkan::createDebugMessenger(m_VulkanInstance, m_Dispatcher);
#endif

		m_PhysicalDevice = vulkan::selectPhysicalDevice(m_VulkanInstance);
		m_LogicalDevice = vulkan::createLogicalDevice(m_PhysicalDevice, m_Surface);

		auto queues = vulkan::getQueue(m_PhysicalDevice, m_LogicalDevice, m_Surface);
		m_GraphicsQueue = queues[0];
		m_PresentQueue = queues[1];
	}

	SnowflakeApp::~SnowflakeApp()
	{
		delete m_Window;

		m_LogicalDevice.destroy();
		m_VulkanInstance.destroySurfaceKHR(m_Surface);

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

