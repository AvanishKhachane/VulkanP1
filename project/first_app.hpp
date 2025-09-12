#pragma once

#include "veWindow.hpp"
#include "vePipeline.hpp"
#include "engine_device.hpp"
#include "veSwapchain.hpp"

#include <iostream>
#include <memory>
#include <vector>

namespace ve
{
	const string vertshader1 = R"(C:\Users\Public\Documents\VS_files\vulkan\vulkanP1\proj\shaders\VertexShader1.vert.spv)";
	const string fragshader1 = R"(C:\Users\Public\Documents\VS_files\vulkan\vulkanP1\proj\shaders\FragmentShader1.frag.spv)";

	class firstapp
	{
	private:
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