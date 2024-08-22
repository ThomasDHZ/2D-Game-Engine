#pragma once
extern "C"
{
	#include <Global.h>
	#include <TextureBase.h>
	#include <Buffer.h>
}
#include <cmath>
#include <algorithm>
#include <string>
#include "VulkanBuffer.h"

class Texture
{
	private:
		uint64_t TextureBufferIndex = 0;

	protected:
		uint32_t Width = 0;
		uint32_t Height = 0;
		uint32_t Depth = 0;
		uint32_t MipMapLevels = 0;

		TextureUsageEnum TextureUsage = TextureUsageEnum::kUse_Undefined;
		TextureTypeEnum TextureType = TextureTypeEnum::kType_UndefinedTexture;
		VkFormat TextureByteFormat = VK_FORMAT_UNDEFINED;
		VkImageLayout TextureImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		VkSampleCountFlagBits SampleCount = VK_SAMPLE_COUNT_1_BIT;

		TextureInfo* SendCTextureInfo();
		void LoadTexture(const std::string& FilePath);
	public:
		Texture();
		Texture(int a);
		Texture(const TextureInfo& textureLoader);
};

