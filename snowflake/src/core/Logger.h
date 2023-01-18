#pragma once
#include "spdlog/spdlog.h"
#include "API.h"

namespace snow
{
	SNOW_API void initializeLogger();
}

#if defined(_DEBUG) || defined(NDEBUG)
	#define SNOW_WARN(...)		::spdlog::warn(__VA_ARGS__)
	#define SNOW_ERROR(...)		::spdlog::error(__VA_ARGS__)
	#define SNOW_CRITICAL(...)	::spdlog::critical(__VA_ARGS__)
#else
	#define DAT_CORE_WARN(...)
	#define DAT_CORE_ERROR(...)
	#define DAT_CORE_CRITICAL(...)
#endif

#if defined(_DEBUG)
	#define SNOW_DEBUG(...)		::spdlog::debug(__VA_ARGS__)
	#define SNOW_TRACE(...)		::spdlog::trace(__VA_ARGS__)
	#define SNOW_INFO(...)		::spdlog::info(__VA_ARGS__)
#else
	#define SNOW_DEBUG(...)
	#define SNOW_TRACE(...)
	#define SNOW_INFO(...)
	
	#define SNOW_WARN(...)
	#define SNOW_ERROR(...)
#endif
