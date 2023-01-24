#pragma once
#include "SnowWindow.h"
#include <vulkan/vulkan.hpp>

namespace snow
{
    class SNOW_API SnowflakeApp
    {
    public:
        // Todo: Use a configuration struct + file.
        SnowflakeApp(int width, int height, const char* title, const char* applicationName = "App");

        virtual ~SnowflakeApp();

    public:
        void run();

    // Todo: abstract these properties.
    private:
        vk::Instance m_VulkanInstance;
        vk::SurfaceKHR m_Surface;

        vk::DebugUtilsMessengerEXT m_DebugMessenger = nullptr;
        vk::DispatchLoaderDynamic m_Dispatcher;

        vk::PhysicalDevice m_PhysicalDevice;
        vk::Device m_LogicalDevice;

        vk::Queue m_GraphicsQueue = nullptr;
        vk::Queue m_PresentQueue = nullptr;

    private:
        SnowWindow* m_Window;
    };
}
