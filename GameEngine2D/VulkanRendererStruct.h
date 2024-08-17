#pragma once
#include <vulkan/vulkan.h>

typedef struct
{
	VkRenderPass RenderPass;
	VkAttachmentDescription* pAttachmentList;
	uint32_t	 Width;
	uint32_t	 Height;
}Renderer_CommandFrameBufferInfo;

typedef struct
{
	VkRenderPass* pRenderPass;
	VkRenderPassCreateInfo* pRenderPassCreateInfo;
}Renderer_RenderPassCreateInfo;