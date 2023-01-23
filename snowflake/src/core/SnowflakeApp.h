#pragma once
#include "SnowWindow.h"

namespace snow
{
    class SNOW_API SnowflakeApp
    {
    public:
        // Todo: Use a configuration struct + file.
        SnowflakeApp(int width, int height, const char* title);

        virtual ~SnowflakeApp();

    public:
        void run();

    private:
        SnowWindow* m_Window;
    };
}
