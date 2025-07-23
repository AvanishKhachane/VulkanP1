#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string>

using namespace std;

namespace ve
{
	class veWindow
	{
	private:

		const int width, height;

		string name;
		GLFWwindow* window;
	public:
		veWindow(const int width, const int height, const string name);

		veWindow(const veWindow&) = delete;
		veWindow &operator=(const veWindow&) = delete;

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

		void initWindow();

		VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; };

		inline bool shouldClose() { return glfwWindowShouldClose(window); };

		~veWindow();
	};
}