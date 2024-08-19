#include "InterfaceRenderPass.h"

VkRenderPass InterfaceRenderPass::RenderPass = VK_NULL_HANDLE;
VkDescriptorPool InterfaceRenderPass::ImGuiDescriptorPool = VK_NULL_HANDLE;
VkCommandPool InterfaceRenderPass::ImGuiCommandPool = VK_NULL_HANDLE;
std::vector<VkFramebuffer> InterfaceRenderPass::SwapChainFramebuffers;
std::vector<VkCommandBuffer> InterfaceRenderPass::ImGuiCommandBuffers;