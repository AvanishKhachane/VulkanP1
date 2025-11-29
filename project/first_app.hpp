#pragma once

#include "veWindow.hpp"
#include "vePipeline.hpp"
#include "engine_device.hpp"
#include "veSwapchain.hpp"
#include "veModel.hpp"

#include <iostream>
#include <memory>
#include <vector>

namespace ve
{
	const string vertshader1 = R"(D:\Docs\vscproj\projects\VulkanP1\project\output\VertexShader1.vert.spv)";
	const string fragshader1 = R"(D:\Docs\vscproj\projects\VulkanP1\project\output\FragmentShader1.frag.spv)";

	class firstapp
	{
	private:
		void loadModel();
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffer();
		void drawFrame();

		veWindow veWin{WIDTH, HEIGHT, "Hello Vulkan"};
		EngineDevice engdev{veWin};
		veSwapChain veSwapchain{engdev, veWin.getExtent()};
		std::unique_ptr<vePipeline> vePl;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		std::unique_ptr<veModel> veMod;

	public:
		firstapp();
		~firstapp();

		firstapp(const firstapp &) = delete;
		firstapp &operator=(const firstapp &) = delete;

		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 800;

		void run();
	};
}