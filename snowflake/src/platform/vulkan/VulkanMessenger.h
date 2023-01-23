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
		SNOW_LOG_ERROR("Validation Layer: {}", callbackData->pMessage);
		return VK_FALSE;
	}
}

namespace snow::vulkan
{
	inline vk::DebugUtilsMessengerEXT createDebugMessenger(vk::Instance& instance, vk::DispatchLoaderDynamic& dispatcher)
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