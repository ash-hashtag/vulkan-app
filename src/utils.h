#pragma once
#include <iostream>
#include <cstring>
#include <chrono>
#include <vector>
#include <set>
#include <optional>
#include <thread>
#include <algorithm>
#include <fstream>


//#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>


#define RST "\x1B[0m"
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YLW "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"

#define WIDTH 800
#define HEIGHT 600
#define APP_NAME "Vulkan App"
#define print(x) std::cout<<x

#define MAX_FRAMES_IN_FLIGHT 2

#define STARTTIMER const auto start = std::chrono::high_resolution_clock::now()
#define TIMESTAMP (std::chrono::high_resolution_clock::now() - start).count() * 0.000001
#define LOGTS() printf(BLU"%f ms\n" RST, TIMESTAMP);
#define LOGTST(x) printf(BLU"%s at: %f ms\n" RST, x, TIMESTAMP);

STARTTIMER;

struct Timer {
	std::chrono::high_resolution_clock::time_point start;
	Timer() : start(std::chrono::high_resolution_clock::now()) {}
	inline void TimeStamp() {
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = (end - start).count() * 0.000001;
		printf("%f ms\n", duration);
	}inline void TimeStamp(const char* point) {
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = (end - start).count() * 0.000001;
		printf("%s: %f ms\n", point, duration);
	}
};

#ifndef NDEBUG 
const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

bool checkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProps : availableLayers) {
			if (strcmp(layerName, layerProps.layerName) == 0) {
				layerFound = true;
				break;
			}
		}
		if (!layerFound) {
			return false;
		}
	}
	return true;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallBack(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData
) {
	//std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;
	printf(YLW"%f ms:" RST " %s\n", TIMESTAMP, pCallbackData->pMessage);
	return VK_FALSE;
}

#endif
const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };



struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	inline bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};




std::vector<const char*> getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
#ifndef  NDEBUG
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
	return extensions;
}

std::vector<char> readFile(const std::string& fileName) {
	std::ifstream file(fileName, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open shader file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

