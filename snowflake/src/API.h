#pragma once
#include <numeric>

// Debug:
#if defined(_DEBUG) || defined(NDEBUG)
	#if !defined(SNOW_DEBUG)
		#define SNOW_DEBUG
	#endif
#endif

// Definitions:
using U8  = std::uint8_t;
using U16 = std::uint16_t;
using U32 = std::uint32_t;
using U64 = std::uint64_t;

using I8  = std::int8_t;
using I16 = std::int16_t;
using I32 = std::int32_t;
using I64 = std::int64_t;

using F32 = std::float_t;
using F64 = std::double_t;

using B8  = bool;
using B16 = std::int16_t;
using B32 = std::int32_t;

// DLL Exports & Imports
#ifdef SNOW_EXPORT

	#ifdef _MSC_VER
		#define SNOW_API __declspec(dllexport)
	#else
		#define SNOW_API
	#endif

#elif SNOW_IMPORT

	#ifdef _MSC_VER
		#define SNOW_API __declspec(dllimport)
	#else
		#define SNOW_API
	#endif

#endif

// Plaftorm Detection:
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32)
	#define SNOW_WINDOWS_PLATFORM
	
	#ifndef _WIN64
		#error "Even if it is not be required at the moment, x64 is certainly going to be required in the future."
	#endif
#elif defined(__linux__) || defined(__gnu_linux__)
	#define SNOW_LINUX_PLATFORM
#else
	#error "Currently, only Windows and Linux are supported."
#endif
