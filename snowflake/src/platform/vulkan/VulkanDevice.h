#pragma once
#include "pch.h"
#include "core/Logger.h"
#include "VulkanQueueFamily.h"

namespace
{
	inline bool checkDeviceExtensionSupport(const vk::PhysicalDevice& device, const std::vector<const char*>& extensionsToCheck)
	{
		std::unordered_set<std::string> requestedExtensions(extensionsToCheck.begin(), extensionsToCheck.end());

		for (auto& extension : device.enumerateDeviceExtensionProperties())
			requestedExtensions.erase(extension.extensionName);

		return requestedExtensions.empty();
	}

	inline bool isDeviceSuitable(const vk::PhysicalDevice& device)
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
	inline void displayDeviceProperties(const vk::PhysicalDevice& device)
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
	inline vk::PhysicalDevice selectPhysicalDevice(const vk::Instance& instance)
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

	inline vk::Device createLogicalDevice(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface)
	{
		QueueFamilyIndices indices = findFamilyQueues(device, surface);

		std::vector<uint32_t> uniqueIndices;
		uniqueIndices.push_back(indices.graphicsFamily.value());

		if (indices.graphicsFamily.value() != indices.presentFamily.value())
			uniqueIndices.push_back(indices.presentFamily.value());

		float priority = 1.f;
		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfo;
		for(const auto& familyIndex : uniqueIndices)
		{
			queueCreateInfo.emplace_back(
				vk::DeviceQueueCreateFlags(),		// flags_
				indices.graphicsFamily.value(),		// queueFamilyIndex_
				1,									// queueCount_
				&priority							// pQueuePriorities_
			);
		};

		vk::PhysicalDeviceFeatures features { };

		std::vector<const char*> enabledLayers;

#ifdef SNOW_DEBUG
		enabledLayers.push_back("VK_LAYER_KHRONOS_validation");
#endif

		vk::DeviceCreateInfo deviceCreateInfo {
			vk::DeviceCreateFlags(),						// flags_
			static_cast<uint32_t>(queueCreateInfo.size()),	// queueCreateInfoCount_
			queueCreateInfo.data(),							// pQueueCreateInfos_
			static_cast<uint32_t>(enabledLayers.size()),	// enabledLayerCount_
			enabledLayers.data(),							// ppEnabledLayerNames_
			0,												// enabledExtensionCount_
			nullptr,										// ppEnabledExtensionNames_
			&features										// pEnabledFeatures_
		};

		try
		{
			return device.createDevice(deviceCreateInfo);
		}
		catch (vk::SystemError error)
		{
			SNOW_LOG_CRITICAL("Failed to create a Vulkan logical device.");
			SNOW_LOG_CRITICAL("{}", error.what());
			SNOW_LOG_DEBUG("\n");
		}

		return nullptr;
	}
}