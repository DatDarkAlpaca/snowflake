#pragma once
#include "core/Logger.h"
#include "pch.h"

namespace
{
	// Helpers:
	inline bool areExtensionSupported(std::vector<const char*> extensions)
	{
		std::vector<vk::ExtensionProperties> extensionsSupported = vk::enumerateInstanceExtensionProperties();

#ifdef SNOW_DEBUG
		SNOW_LOG_DEBUG("Supported Extensions:");
		for (const auto& extension : extensionsSupported)
			SNOW_LOG_DEBUG("* {}", extension.extensionName);
		SNOW_LOG_DEBUG("\n");
#endif

		bool supported = true, sticky = true;
		for (const char* extension : extensions)
		{
			supported = false;

			for (const auto& supportedExtension : extensionsSupported)
			{
				if (strcmp(extension, supportedExtension.extensionName) == 0)
				{
					supported = true;
					continue;
				}
			}

			if (!supported)
			{
				SNOW_LOG_ERROR("The following requested extension is not supported: {}", extension);
				sticky = false;
			}
		}

		return sticky && supported;
	}

	inline bool areLayersSupported(std::vector<const char*> layers)
	{
		std::vector<vk::LayerProperties> layersSupported = vk::enumerateInstanceLayerProperties();

#ifdef SNOW_DEBUG
		SNOW_LOG_DEBUG("Supported Layers:");
		for (const auto& layer : layersSupported)
			SNOW_LOG_DEBUG("* {}", layer.layerName);
		SNOW_LOG_DEBUG("\n");
#endif

		bool supported = true, sticky = true;
		for (const char* layer : layers)
		{
			supported = false;

			for (const auto& supportedLayer : layersSupported)
			{
				if (strcmp(layer, supportedLayer.layerName) == 0)
				{
					supported = true;
					continue;
				}
			}

			if (!supported)
			{
				SNOW_LOG_ERROR("The following requested layer is not supported: {}", layer);
				sticky = false;
			}
		}

		return sticky && supported;
	}

	// Version:
	inline uint32_t createVersion()
	{
		uint32_t version{ 0 };
		vkEnumerateInstanceVersion(&version);

		SNOW_LOG_DEBUG("Supported Vulkan Version: {}.{}.{} (Variant: {})",
			VK_API_VERSION_MAJOR(version),
			VK_API_VERSION_MINOR(version),
			VK_API_VERSION_PATCH(version),
			VK_API_VERSION_VARIANT(version)
		);
		SNOW_LOG_DEBUG("\n");

		// Vulkan Version (Zeroed Patch)
		version &= ~(0xFFFU);
		version = VK_MAKE_API_VERSION(0, 1, 0, 0);

		return version;
	}

	// GLFW Extensions:
	inline std::vector<const char*> requestExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef SNOW_DEBUG
		SNOW_LOG_DEBUG("GLFW Extensions:");
		for (const char* extension : extensions)
			SNOW_LOG_DEBUG("* {}", extension);
		SNOW_LOG_DEBUG("\n");
#endif

#ifdef SNOW_DEBUG
		SNOW_LOG_DEBUG("Debug Extensions:");
		SNOW_LOG_DEBUG("* VK_EXT_debug_utils");
		SNOW_LOG_DEBUG("\n");

		extensions.push_back("VK_EXT_debug_utils");
#endif

		return extensions;
	}
}

namespace snow::vulkan
{
	inline vk::Instance createInstance(const char* applicationName = "Application", const char* engineName = "Snowflake Engine")
	{
		// Version:
		uint32_t version = createVersion();

		// Application Info:
		vk::ApplicationInfo appInfo{
			applicationName, // pApplicationName_
			version,		 // applicationVersion_
			engineName,		 // pEngineName_
			version,		 // engineVersion_
			version			 // apiVersion_
		};

		// Extensions:
		std::vector<const char*> extensions = requestExtensions();

		// Layers:
		std::vector<const char*> layers;

#ifdef SNOW_DEBUG
		layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

		// Supported:
		if (!areExtensionSupported(extensions) || !areLayersSupported(layers))
			return nullptr;

		// Create Info:
		vk::InstanceCreateInfo createInfo{
			vk::InstanceCreateFlags(),					// flags_
			&appInfo,									// pApplicationInfo_
			static_cast<uint32_t>(layers.size()),		// enabledLayerCount_
			layers.data(),								// ppEnabledLayerNames_
			static_cast<uint32_t>(extensions.size()),	// enabledExtensionCount_
			extensions.data()							// ppEnabledExtensionNames_
		};

		// Instance:
		try
		{
			return vk::createInstance(createInfo, nullptr);
		}
		catch (vk::SystemError error)
		{
			SNOW_LOG_CRITICAL("Failed to create a Vulkan instance.");
			SNOW_LOG_CRITICAL("{}", error.what());
			SNOW_LOG_DEBUG("\n");

			return nullptr;
		}
	}
}