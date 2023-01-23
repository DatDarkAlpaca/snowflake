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

    private:
        SnowWindow* m_Window;
    };
}
