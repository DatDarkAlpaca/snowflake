#include "pch.h"
#include "Logger.h"

void snow::initializeLogger()
{
#if defined(SNOW_DEBUG)
	spdlog::set_level(spdlog::level::trace);
#endif
}
