#include "veWindow.hpp"
#include <iostream>
#include <stdexcept>

namespace ve
{
	veWindow::veWindow(const int width, const int height, const string name)
		: width(width), height(height), name(name) 
	{
		initWindow();
	}

	void veWindow::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	};
	
	void veWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		VkResult val = glfwCreateWindowSurface(instance, window, nullptr, surface);
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
		{
			std::cout << val << std::endl;
			throw std::runtime_error("failed to create window surface!");
		}
	}


	veWindow::~veWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	};
}