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

    static std::vector<VkVertexInputBindingDescription> getBindingDescriptions()
    {
        std::vector<VkVertexInputBindingDescription>  bindingDescriptionList{};
        VkVertexInputBindingDescription bindingDescription{};

        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex2D);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        bindingDescriptionList.emplace_back(bindingDescription);

        return bindingDescriptionList;
    }

    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions()
    {
        std::vector<VkVertexInputAttributeDescription> AttributeDescriptions = {};

        VkVertexInputAttributeDescription AttributeDescription;

        AttributeDescription.binding = 0;
        AttributeDescription.location = 0;
        AttributeDescription.format = VK_FORMAT_R32G32_SFLOAT;
        AttributeDescription.offset = offsetof(Vertex2D, Position);
        AttributeDescriptions.emplace_back(AttributeDescription);

        AttributeDescription.binding = 0;
        AttributeDescription.location = 1;
        AttributeDescription.format = VK_FORMAT_R32G32_SFLOAT;
        AttributeDescription.offset = offsetof(Vertex2D, UV);
        AttributeDescriptions.emplace_back(AttributeDescription);

        AttributeDescription.binding = 0;
        AttributeDescription.location = 2;
        AttributeDescription.format = VK_FORMAT_R32G32B32A32_SFLOAT;
        AttributeDescription.offset = offsetof(Vertex2D, Color);
        AttributeDescriptions.emplace_back(AttributeDescription);

        return AttributeDescriptions;
    }
};
//struct Vertex2D
//{
//    glm::vec2 Position = glm::vec2(0.0f);
//    glm::vec2 UV = glm::vec2(0.0f);
//    glm::vec4 Color = glm::vec4(1.0f);
//
//    static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions()
//    {
//        return
//        {
//            VkVertexInputBindingDescription
//            {
//                .binding = 0,
//                .stride = sizeof(Vertex2D),
//                .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
//            }
//        };
//    }
//
//    static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions()
//    {
//        return  
//        {
//            VkVertexInputAttributeDescription
//            {
//                .location = 0,
//                .binding = 0,
//                .format = VK_FORMAT_R32G32_SFLOAT,
//                .offset = offsetof(Vertex2D, Position)
//            },
//            VkVertexInputAttributeDescription
//            {
//                .location = 0,
//                .binding = 1,
//                .format = VK_FORMAT_R32G32_SFLOAT,
//                .offset = offsetof(Vertex2D, UV)
//            },
//            VkVertexInputAttributeDescription
//            {
//                .location = 0,
//                .binding = 2,
//                .format = VK_FORMAT_R32G32B32A32_SFLOAT,
//                .offset = offsetof(Vertex2D, Color)
//            }
//        };
//    }
//};

