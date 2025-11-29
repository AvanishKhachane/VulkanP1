#pragma once

#define GLM_FORCE_RADIANS
#define	 FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

#include "engine_device.hpp"

namespace ve
{
	class veModel
	{
	public:

		struct Vertex
		{
			glm::vec2 position;
			glm::vec3 color;

			static std::vector<VkVertexInputBindingDescription> getBindingDescription();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescription();
		};

		veModel(EngineDevice& engdev, const std::vector<Vertex>& vertices);
		~veModel();

		veModel(const veModel&) = delete;
		veModel& operator = (const veModel&) = delete;

		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer);

	private:
		EngineDevice& engdev;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		uint32_t vertexCount;

		void createVertexBuffer(const std::vector<Vertex>& vertices);
	};
}