#pragma once
#include "core/Logger.h"
#include "pch.h"

namespace
{
	bool checkDeviceExtensionSupport(const vk::PhysicalDevice& device, const std::vector<const char*>& extensionsToCheck)
	{
		std::unordered_set<std::string> requestedExtensions(extensionsToCheck.begin(), extensionsToCheck.end());

		for (auto& extension : device.enumerateDeviceExtensionProperties())
			requestedExtensions.erase(extension.extensionName);

		return requestedExtensions.empty();
	}

	bool isDeviceSuitable(const vk::PhysicalDevice& device)
	{
		std::vector<const char*> requestedExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

#ifdef SNOW_DEBUG
		SNOW_LOG_DEBUG("Requested Extensions:");
		for (const char* extension : requestedExtensions)
			SNOW_LOG_DEBUG("* {}", extension);
#endif

		bool extensionsSupported = checkDeviceExtensionSupport(device, requestedExtensions);
		if (!extensionsSupported)
		{
			SNOW_LOG_ERROR("This device does not support the required extensions");
			return false;
		}

		SNOW_LOG_DEBUG("\n");

		return true;
	}

#ifdef SNOW_DEBUG
	void displayDeviceProperties(const vk::PhysicalDevice& device)
	{
		vk::PhysicalDeviceProperties properties = device.getProperties();

		SNOW_LOG_DEBUG("-= Device Name: {} (ID : {}) =-", properties.deviceName, properties.deviceID);
		SNOW_LOG_DEBUG("API Version: {}", properties.apiVersion);
		SNOW_LOG_DEBUG("Driver Version: {}", properties.driverVersion);

		std::string deviceType;
		switch (properties.deviceType)
		{
		case vk::PhysicalDeviceType::eCpu:
			deviceType = "CPU";
			break;

		case vk::PhysicalDeviceType::eDiscreteGpu:
			deviceType = "Discrete GPU";
			break;

		case vk::PhysicalDeviceType::eIntegratedGpu:
			deviceType = "Integrated GPU";
			break;

		case vk::PhysicalDeviceType::eOther:
			deviceType = "Other GPU";
			break;

		case vk::PhysicalDeviceType::eVirtualGpu:
			deviceType = "Virtual GPU";
			break;

		default:
			deviceType = "Unknown GPU Type";
			break;
		}
		SNOW_LOG_DEBUG("Device Type {}", deviceType);
	}
#endif
}

namespace snow::vulkan
{
	vk::PhysicalDevice selectPhysicalDevice(vk::Instance& instance)
	{
		std::vector<vk::PhysicalDevice> avaliableDevices = instance.enumeratePhysicalDevices();
		vk::PhysicalDevice chosenDevice;

#ifdef SNOW_DEBUG
		if (avaliableDevices.size() == 0)
			SNOW_LOG_DEBUG("There are no physical device(s) available");
		else if (avaliableDevices.size() == 1)
			SNOW_LOG_DEBUG("There is one device available");
		else
			SNOW_LOG_DEBUG("There are {}x device(s) available", avaliableDevices.size());

		SNOW_LOG_DEBUG("\n");

		for (const auto& device : avaliableDevices)
		{
			displayDeviceProperties(device);
			SNOW_LOG_DEBUG("\n");
		}
#endif

		for (const auto& device : avaliableDevices)
		{
			if (isDeviceSuitable(device))
				return device;
		}

		SNOW_LOG_ERROR("Unable to find a suitable physical device.");
		return nullptr;
	}
}