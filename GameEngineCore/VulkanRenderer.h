#pragma once
#include <windows.h>
#pragma warning(push)
#pragma warning(disable : 26819) 
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#pragma warning(pop)
#include <stdbool.h>

#include "Macro.h"
#include "CTypedef.h"
#include "VulkanRendererStruct.h"
#include "VulkanSwapChain.h"
#include "VulkanError.h"

static const int MAX_FRAMES_IN_FLIGHT = 3;

typedef struct rendererState
{
	 VkInstance Instance;
	 VkDevice Device;
	 VkPhysicalDevice PhysicalDevice;
	 VkSurfaceKHR Surface;
	 VkCommandPool CommandPool;
	 uint32 ImageIndex;
	 uint32 CommandIndex;
	 VkDebugUtilsMessengerEXT DebugMessenger;
	 SwapChainState SwapChain;
	 VkPhysicalDeviceFeatures PhysicalDeviceFeatures;

	 VkFence* InFlightFences;
	 VkSemaphore* AcquireImageSemaphores;
	 VkSemaphore* PresentImageSemaphores;
	 bool RebuildRendererFlag;
}RendererState;

VkResult Renderer_RendererSetUp();
VkResult Renderer_RebuildSwapChain();
VkResult Renderer_CreateCommandBuffers(VkCommandBuffer* pCommandBufferList);
VkResult Renderer_CreateFrameBuffer(VkFramebuffer* pFrameBuffer, VkFramebufferCreateInfo* frameBufferCreateInfo);
VkResult Renderer_CreateRenderPass(Renderer_RenderPassCreateInfoStruct* pRenderPassCreateInfo);
VkResult Renderer_CreateDescriptorPool(VkDescriptorPool* descriptorPool, VkDescriptorPoolCreateInfo* descriptorPoolCreateInfo);
VkResult Renderer_CreateDescriptorSetLayout(VkDescriptorSetLayout* descriptorSetLayout, VkDescriptorSetLayoutCreateInfo* descriptorSetLayoutCreateInfo);
VkResult Renderer_CreatePipelineLayout(VkPipelineLayout* pipelineLayout, VkPipelineLayoutCreateInfo* pipelineLayoutCreateInfo);
VkResult Renderer_AllocateDescriptorSets(VkDescriptorSet* descriptorSet, VkDescriptorSetAllocateInfo* descriptorSetAllocateInfo);
VkResult Renderer_AllocateCommandBuffers(VkCommandBuffer* commandBuffer, VkCommandBufferAllocateInfo* ImGuiCommandBuffers);
VkResult Renderer_CreateGraphicsPipelines(VkPipeline* graphicPipeline, VkGraphicsPipelineCreateInfo* createGraphicPipelines, uint32 createGraphicPipelinesCount);
VkResult Renderer_CreateCommandPool(VkCommandPool* commandPool, VkCommandPoolCreateInfo* commandPoolInfo);
VkResult Renderer_StartFrame();
VkResult Renderer_EndFrame(VkCommandBuffer* pCommandBufferSubmitList, uint32 commandBufferCount);
VkResult Renderer_BeginCommandBuffer( VkCommandBuffer* pCommandBuffer, VkCommandBufferBeginInfo* commandBufferBeginInfo);
VkResult Renderer_EndCommandBuffer(VkCommandBuffer* pCommandBuffer);
VkResult Renderer_SubmitDraw(VkCommandBuffer* pCommandBufferSubmitList);

uint32 Renderer_GetMemoryType(uint32 typeFilter, VkMemoryPropertyFlags properties);
VkCommandBuffer Renderer_BeginSingleUseCommandBuffer();
VkResult Renderer_EndSingleUseCommandBuffer(VkCommandBuffer commandBuffer);

void Renderer_UpdateDescriptorSet(VkWriteDescriptorSet* writeDescriptorSet, uint32 count);
void Renderer_DestroyRenderer();
void Renderer_DestroyFences();
void Renderer_DestroyCommandPool();
void Renderer_DestroyDevice();
void Renderer_DestroySurface();
void Renderer_DestroyDebugger();
void Renderer_DestroyInstance();
void Renderer_DestroyRenderPass(VkRenderPass* renderPass);
void Renderer_DestroyFrameBuffers(VkFramebuffer* frameBufferList);
void Renderer_DestroyDescriptorPool(VkDescriptorPool* descriptorPool);
void Renderer_DestroyDescriptorSetLayout(VkDescriptorSetLayout* descriptorSetLayout);
void Renderer_DestroyCommandBuffers(VkCommandPool* commandPool, VkCommandBuffer* commandBufferList);
void Renderer_DestroyCommnadPool(VkCommandPool* commandPool);
void Renderer_DestroyBuffer(VkBuffer* buffer);
void Renderer_DestroyImageView(VkImageView* imageView);
void Renderer_DestroyImage(VkImage* image);
void Renderer_DestroySampler(VkSampler* sampler);
void Renderer_DestroyPipeline(VkPipeline* pipeline);
void Renderer_DestroyPipelineLayout(VkPipelineLayout* pipelineLayout);
void Renderer_DestroyPipelineCache(VkPipelineCache* pipelineCache);
void Renderer_FreeMemory(VkDeviceMemory* memory);
