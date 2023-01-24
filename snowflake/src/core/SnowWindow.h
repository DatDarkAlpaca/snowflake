#pragma once
#include <GLFW/glfw3.h>
#include "Logger.h"

namespace snow
{
    inline void GLFWErrorCallback(int errorCode, const char* description)
    {
        SNOW_LOG_ERROR("GLFW Error [{}]: {}", errorCode, description);
    }

    class SnowWindow
    {
    private:
        struct SnowWindowDeleter
        {
            void operator()(GLFWwindow* window);
        };

    public:
        SnowWindow(int width, int height, const char* title);

        SnowWindow() = default;

    public:
        GLFWwindow* get() const { return m_Window.get(); }

    private:
        std::unique_ptr<GLFWwindow, SnowWindowDeleter> m_Window = nullptr;
    };
}

