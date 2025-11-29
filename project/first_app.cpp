#include "first_app.hpp"

#include <stdexcept>
#include <array>

namespace ve
{
	firstapp::firstapp()
	{
		loadModel();
		createPipelineLayout();
		createPipeline();
		createCommandBuffer();
	}

	firstapp::~firstapp()
	{
		vkDestroyPipelineLayout(engdev.device(), pipelineLayout, nullptr);
	}

	void firstapp::run()
	{
		while (!veWin.shouldClose())
		{
			glfwPollEvents();
			drawFrame();
		}
		vkDeviceWaitIdle(engdev.device());
	}

	void firstapp::createPipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(engdev.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create pipeline layout!");
		}
	}

	void firstapp::createPipeline()
	{
		auto pipelineConfig = vePipeline::defaultPiplineConfigInfo(veSwapchain.width(), veSwapchain.height());
		pipelineConfig.renderPass = veSwapchain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		vePl = std::make_unique<vePipeline>(engdev, vertshader1, fragshader1, pipelineConfig);
	};

	void firstapp::createCommandBuffer()
	{
		commandBuffers.resize(veSwapchain.imageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = engdev.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(engdev.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate command buffers!");
		}

		for (int i = 0; i < commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to begin recording command buffer!");
			}
			
			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = veSwapchain.getRenderPass();
			renderPassInfo.framebuffer = veSwapchain.getFrameBuffer(i);
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = veSwapchain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.01f, 0.01f, 0.01f, 1.0f };
			clearValues[1].depthStencil = { 1.0f, 0 };
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
			vePl->bind(commandBuffers[i]);
			veMod->bind(commandBuffers[i]);
			veMod->draw(commandBuffers[i]);
			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to record command buffer!");
			}

		}
	}

	void firstapp::drawFrame()
	{
		uint32_t imageIndex;
		auto result = veSwapchain.acquireNextImage(&imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			throw std::runtime_error("failed to acquire swap chain image!");
		}
		
		result = veSwapchain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("failed to present swap chain image!");
		}
	}

	void firstapp::loadModel()
	{
		std::vector<veModel::Vertex> vertices = {
			{{0.0f, -0.4f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};

		veMod = std::make_unique<veModel>(engdev, vertices);
	}
}