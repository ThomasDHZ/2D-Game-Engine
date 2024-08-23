#pragma once
extern "C"
{
	#include <Global.h>
	#include <CTexture.h>
	#include <CBuffer.h>
}
#include <cmath>
#include <algorithm>
#include <string>
#include "VulkanBuffer.h"
#include "ImGui/imgui_impl_vulkan.h"

class Texture
{
	private:
		uint64_t TextureBufferIndex;
		VkDescriptorSet ImGuiDescriptorSet;
		VkImage Image;
		VkDeviceMemory Memory;
		VkImageView View;
		VkSampler Sampler;

	protected:
		int Width;
		int Height;
		int Depth;
		uint32_t MipMapLevels;

		TextureUsageEnum TextureUsage = TextureUsageEnum::kUse_Undefined;
		TextureTypeEnum TextureType = TextureTypeEnum::kType_UndefinedTexture;
		VkFormat TextureByteFormat = VK_FORMAT_UNDEFINED;
		VkImageLayout TextureImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		VkSampleCountFlagBits SampleCount = VK_SAMPLE_COUNT_1_BIT;

		std::unique_ptr<TextureInfo> SendCTextureInfo();
		void LoadTexture(const std::string& FilePath);
		void CreateTextureView();
		void CreateTextureSampler();
		void ImGuiShowTexture(const ImVec2& TextureDisplaySize);

	public:
		Texture();
		Texture(const std::string& filePath, VkFormat textureByteFormat, TextureTypeEnum TextureType);
};

