#pragma once
#include "core/Logger.h"
#include "pch.h"

namespace
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isValid() const
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

}

namespace snow::vulkan
{
	QueueFamilyIndices findFamilyQueues(const vk::PhysicalDevice& device)
	{
		QueueFamilyIndices indices;

		std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

#ifdef SNOW_DEBUG
		if (queueFamilies.size() == 0)
			SNOW_LOG_DEBUG("The system can not support any queue families.");
		else if (queueFamilies.size() == 1)
			SNOW_LOG_DEBUG("The system can support one queue family.");
		else
			SNOW_LOG_DEBUG("The system can support {}x queue families.", queueFamilies.size());

		SNOW_LOG_DEBUG("\n");
#endif

		for (size_t i = 0; i < queueFamilies.size(); ++i)
		{
			if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
			{
				indices.graphicsFamily = i;
				indices.presentFamily = i;
				SNOW_LOG_DEBUG("The queue #{} was determined to be suitable for graphics and presentation.", i);
			}

			if (indices.isValid())
				break;
		}

		return indices;
	}

	vk::Queue getQueue(const vk::PhysicalDevice& physicalDevice, const vk::Device& logicalDevice)
	{
		QueueFamilyIndices indices = findFamilyQueues(physicalDevice);

		return logicalDevice.getQueue(indices.graphicsFamily.value(), 0);
	}
}