#include "pch.h"
#include "Logger.h"

void snow::initializeLogger()
{
#if defined(_DEBUG)
	spdlog::set_level(spdlog::level::trace);
#endif
}
