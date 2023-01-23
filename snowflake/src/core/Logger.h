#pragma once
#include "spdlog/spdlog.h"
#include "API.h"

namespace snow
{
	SNOW_API void initializeLogger();
}

#if defined(_DEBUG) || defined(NDEBUG)
	#define SNOW_LOG_WARN(...)		::spdlog::warn(__VA_ARGS__)
	#define SNOW_LOG_ERROR(...)		::spdlog::error(__VA_ARGS__)
	#define SNOW_LOG_CRITICAL(...)	::spdlog::critical(__VA_ARGS__)
#else
	#define SNOW_LOG_WARN(...)
	#define SNOW_LOG_ERROR(...)
	#define SNOW_LOG_CRITICAL(...)
#endif

#if defined(_DEBUG)
	#define SNOW_LOG_DEBUG(...)		::spdlog::debug(__VA_ARGS__)
	#define SNOW_LOG_TRACE(...)		::spdlog::trace(__VA_ARGS__)
	#define SNOW_LOG_INFO(...)		::spdlog::info(__VA_ARGS__)
#else
	#define SNOW_LOG_DEBUG(...)
	#define SNOW_LOG_TRACE(...)
	#define SNOW_LOG_INFO(...)

	#define SNOW_LOG_WARN(...)
	#define SNOW_LOG_ERROR(...)
#endif
