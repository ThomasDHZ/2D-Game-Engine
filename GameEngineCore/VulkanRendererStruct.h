#pragma once
#include <vulkan/vulkan.h>

typedef struct
{
	VkRenderPass*					pRenderPass;
	const VkAttachmentDescription*  pAttachmentList;
	const VkSubpassDescription*		pSubpassDescriptionList;
	const VkSubpassDependency*		pSubpassDependencyList;
	uint32_t						AttachmentCount;
	uint32_t						SubpassCount;
	uint32_t						DependencyCount;
	uint32_t						Width;
	uint32_t						Height;
}Renderer_RenderPassCreateInfoStruct;