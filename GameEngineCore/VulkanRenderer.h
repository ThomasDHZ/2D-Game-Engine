#pragma once
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include "Macro.h"
#include "io.h"
#include "VulkanRendererStruct.h"
#include "GraphicsDevice.h"
#include "VulkanSwapChain.h"
#include "Window.h"
#include "CArray.h"


static const int MAX_FRAMES_IN_FLIGHT = 3;

typedef struct rendererState
{
	 VkInstance Instance;
	 VkDevice Device;
	 VkPhysicalDevice PhysicalDevice;
	 VkSurfaceKHR Surface;
	 VkCommandPool CommandPool;
	 uint32_t ImageIndex;
	 uint32_t CommandIndex;
	 VkDebugUtilsMessengerEXT DebugMessenger;
	 SwapChainState SwapChain;
	 VkPhysicalDeviceFeatures PhysicalDeviceFeatures;

	 VkFence* InFlightFences;
	 VkSemaphore* AcquireImageSemaphores;
	 VkSemaphore* PresentImageSemaphores;
	 bool RebuildSwapChainFlag;
}RendererState;

void Renderer_RendererSetUp();
void Renderer_CreateCommandBuffers(VkCommandBuffer* pCommandBufferList);
void Renderer_CreateFrameBuffer(Renderer_CommandFrameBufferInfoStruct* pCreateCommandBufferInfo);
void Renderer_CreateRenderPass(Renderer_RenderPassCreateInfoStruct* pRenderPassCreateInfo);
void Renderer_StartFrame();
void Renderer_EndFrame(VkCommandBuffer* pCommandBufferSubmitList, uint32_t commandBufferCount);
void Renderer_BeginCommandBuffer(Renderer_BeginCommandBufferStruct* pBeginCommandBufferInfo);
void Renderer_EndCommandBuffer(VkCommandBuffer* pCommandBuffer);
void Renderer_SubmitDraw(VkCommandBuffer* pCommandBufferSubmitList);

uint32_t Renderer_GetMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
VkCommandBuffer Renderer_BeginSingleUseCommandBuffer();
VkResult Renderer_EndSingleUseCommandBuffer(VkCommandBuffer* commandBuffer);

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
void Renderer_DestroyBufferMemory(VkDeviceMemory* deviceMemory);
void Renderer_DestroyBuffer(VkBuffer* buffer);
void Renderer_DestroyImageView(VkImageView* imageView);
void Renderer_DestroyImage(VkImage* image);
void Renderer_DestroySampler(VkSampler* sampler);
void Renderer_DestroyPipeline(VkPipeline* pipeline);
void Renderer_DestroyPipelineLayout(VkPipelineLayout* pipelineLayout);
void Renderer_DestroyPipelineCache(VkPipelineCache* pipelineCache);
void Renderer_FreeMemory(VkDeviceMemory* memory);