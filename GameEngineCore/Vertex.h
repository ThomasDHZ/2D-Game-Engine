#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <vulkan/vulkan_core.h>

struct Vertex2D
{
    glm::vec2 Position = glm::vec2(0.0f);
    glm::vec2 UV = glm::vec2(0.0f);
    glm::vec4 Color = glm::vec4(1.0f);

    static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions()
    {
        return
        {
            VkVertexInputBindingDescription
            {
                .binding = 0,
                .stride = sizeof(Vertex2D),
                .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
            }
        };
    }

    static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions()
    {
        return  
        {
            VkVertexInputAttributeDescription
            {
                .location = 0,
                .binding = 0,
                .format = VK_FORMAT_R32G32_SFLOAT,
                .offset = offsetof(Vertex2D, Position)
            },
            VkVertexInputAttributeDescription
            {
                .location = 0,
                .binding = 1,
                .format = VK_FORMAT_R32G32_SFLOAT,
                .offset = offsetof(Vertex2D, UV)
            },
            VkVertexInputAttributeDescription
            {
                 .location = 0,
                .binding = 1,
                .format = VK_FORMAT_R32G32B32A32_SFLOAT,
                .offset = offsetof(Vertex2D, Color)
            }
        };
    }
};

