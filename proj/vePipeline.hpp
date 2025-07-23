#pragma once

#include <string>
#include <vector>

#include "engine_device.hpp"

namespace ve
{

	struct pipelineConfigInfo {
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class vePipeline
	{
	private:
		static std::vector<char> readFile(const std::string& filepath);
		void createPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const pipelineConfigInfo& ConfigInfo);
		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		EngineDevice& device;
		VkPipeline pipeline;
		VkShaderModule vertShaderModule, fragShaderModule;
	public:
		vePipeline(EngineDevice& device, const std::string vertFilePath, const std::string fragFilePath, const pipelineConfigInfo& ConfigInfo);

		~vePipeline();

		vePipeline(const vePipeline&) = delete;
		vePipeline& operator=(const vePipeline&) = delete;
		
		void bind(VkCommandBuffer commandBuffer);

		static pipelineConfigInfo defaultPiplineConfigInfo(uint32_t width, uint32_t height);

	};
}