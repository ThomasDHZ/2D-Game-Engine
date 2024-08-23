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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VulkanBuffer.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_vulkan.h>

class Texture
{
	private:
		uint64_t TextureBufferIndex;

	protected:
		int Width;
		int Height;
		int Depth;
		uint32_t MipMapLevels;

		TextureUsageEnum TextureUsage;
		TextureTypeEnum TextureType;
		VkFormat TextureByteFormat;
		VkImageLayout TextureImageLayout;
		VkSampleCountFlagBits SampleCount;

		std::unique_ptr<TextureInfo> SendCTextureInfo();
		virtual void CreateImageTexture(const std::string& FilePath);
		virtual void CreateTextureView();
		virtual void CreateTextureSampler();

	public:
		VkDescriptorSet ImGuiDescriptorSet;
		VkImage Image;
		VkDeviceMemory Memory;
		VkImageView View;
		VkSampler Sampler;

		Texture();
		Texture(const std::string& filePath, VkFormat textureByteFormat, TextureTypeEnum TextureType);
		virtual ~Texture();
		void ImGuiShowTexture(const ImVec2& TextureDisplaySize);
		const VkFormat GetTextureByteFormat() { return TextureByteFormat; }
		const VkSampleCountFlagBits GetSampleCount() { return SampleCount; }

};

