
#include <cassert>
#include <cstring>

#include "veModel.hpp"

namespace ve
{
	veModel::veModel(EngineDevice& engdev, const std::vector<Vertex>& vertices) : engdev{ engdev }
	{
		createVertexBuffer(vertices);
	}

	veModel::~veModel()
	{
		vkDestroyBuffer(engdev.device(), vertexBuffer, nullptr);
		vkFreeMemory(engdev.device(), vertexBufferMemory, nullptr);
	}

	void veModel::createVertexBuffer(const std::vector<Vertex>& vertices)
	{
		vertexCount = static_cast<uint32_t>(vertices.size());
		assert(vertexCount >= 3 && "Vertex count must be at least 3");
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
		engdev.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer, vertexBufferMemory);
		void* data;
		vkMapMemory(engdev.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(engdev.device(), vertexBufferMemory);
	}
}