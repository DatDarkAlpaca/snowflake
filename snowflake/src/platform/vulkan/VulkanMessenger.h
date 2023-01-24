#pragma once
#include <vulkan/vulkan.hpp>
#include "core/Logger.h"

namespace
{
	VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverityFlags,
		VkDebugUtilsMessageTypeFlagsEXT messageTypeFlags,
		const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		void* userData)
	{
		switch (messageSeverityFlags)
		{
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
				SNOW_LOG_ERROR("Validation Layer: {}", callbackData->pMessage);
				break;

			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
				SNOW_LOG_WARN("Validation Layer: {}", callbackData->pMessage);
				break;

			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
				SNOW_LOG_INFO("Validation Layer: {}", callbackData->pMessage);
				break;

			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
				SNOW_LOG_DEBUG("Validation Layer: {}", callbackData->pMessage);
				break;

			default:
				SNOW_LOG_TRACE("[Unknown Severity] Validation Layer: {}", callbackData->pMessage);
				break;
		}

		return VK_FALSE;
	}
}

namespace snow::vulkan
{
	inline vk::DebugUtilsMessengerEXT createDebugMessenger(const vk::Instance& instance, const vk::DispatchLoaderDynamic& dispatcher)
	{
		vk::DebugUtilsMessengerCreateInfoEXT createDebugMessengerInfo{
			vk::DebugUtilsMessengerCreateFlagsEXT(),
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
			debugUtilsMessengerCallback,
			nullptr
		};

		return instance.createDebugUtilsMessengerEXT(createDebugMessengerInfo, nullptr, dispatcher);
	}
}