#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>

#ifdef max 
#undef max
#endif

Texture::Texture()
{
	TextureBufferIndex = 0;
	Width = 1;
	Height = 1;
	Depth = 1;
	MipMapLevels = 1;

	ImGuiDescriptorSet = VK_NULL_HANDLE;
	Image = VK_NULL_HANDLE;
	Memory = VK_NULL_HANDLE;
	View = VK_NULL_HANDLE;
	Sampler = VK_NULL_HANDLE;

	TextureUsage = TextureUsageEnum::kUse_Undefined;
	TextureType = TextureTypeEnum::kType_UndefinedTexture;
	TextureByteFormat = VK_FORMAT_UNDEFINED;
	TextureImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	SampleCount = VK_SAMPLE_COUNT_1_BIT;
}

Texture::Texture(TextureUsageEnum textureUsage)
{
	TextureUsage = TextureUsageEnum::kUse_Undefined;
}

Texture::Texture(const std::string& filePath, VkFormat textureByteFormat, TextureTypeEnum textureType)
{
	TextureBufferIndex = 0;
	Width = 1;
	Height = 1;
	Depth = 1;
	MipMapLevels = 1;

	ImGuiDescriptorSet = VK_NULL_HANDLE;
	Image = VK_NULL_HANDLE;
	Memory = VK_NULL_HANDLE;
	View = VK_NULL_HANDLE;
	Sampler = VK_NULL_HANDLE;

	TextureUsage = TextureUsageEnum::kUse_Undefined;
	TextureType = textureType;
	TextureByteFormat = textureByteFormat;
	TextureImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	SampleCount = VK_SAMPLE_COUNT_1_BIT;

	CreateImageTexture(filePath);
	CreateTextureView();
	CreateTextureSampler();
	ImGuiDescriptorSet = ImGui_ImplVulkan_AddTexture(Sampler, View, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

Texture::~Texture()
{
}

void Texture::CreateImageTexture(const std::string& FilePath)
{
	int* width = &Width;
	int* height = &Height;
	int colorChannels = 0;
	unsigned char* data = stbi_load(FilePath.c_str(), width, height, &colorChannels, 0);
	VulkanBuffer buffer(data, Width * Height * colorChannels, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	MipMapLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(Width, Height)))) + 1;

	Texture_CreateTextureImage(SendCTextureInfo().get());
	Texture_TransitionImageLayout(SendCTextureInfo().get(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Texture_CopyBufferToTexture(SendCTextureInfo().get(), &buffer.Buffer);
	Texture_GenerateMipmaps(SendCTextureInfo().get());
	Buffer_DestroyBuffer(buffer.SendCBufferInfo().get());
}

void Texture::CreateTextureView()
{
	VkImageViewCreateInfo TextureImageViewInfo = 
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.image = Image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = TextureByteFormat,
		.subresourceRange = VkImageSubresourceRange
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = MipMapLevels,
			.baseArrayLayer = 0,
			.layerCount = 1,
		},
	};
	VkResult result = Texture_CreateTextureView(SendCTextureInfo().get(), &TextureImageViewInfo);
	if (result != VkResult::VK_SUCCESS)
	{

	}
}

void Texture::CreateTextureSampler()
{
	VkSamplerCreateInfo TextureImageSamplerInfo = 
	{
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.magFilter = VK_FILTER_NEAREST,
		.minFilter = VK_FILTER_NEAREST,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
		.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.mipLodBias = 0,
		.anisotropyEnable = VK_TRUE,
		.maxAnisotropy = 16.0f,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_ALWAYS,
		.minLod = 0,
		.maxLod = static_cast<float>(MipMapLevels),
		.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		.unnormalizedCoordinates = VK_FALSE,
	};
	VkResult result = Texture_CreateTextureSampler(SendCTextureInfo().get(), &TextureImageSamplerInfo);
	if (result != VkResult::VK_SUCCESS)
	{

	}
}

std::unique_ptr<TextureInfo> Texture::SendCTextureInfo()
{
	std::unique_ptr<TextureInfo> textureInfo = std::make_unique<TextureInfo>();
	textureInfo->Width = &Width;
	textureInfo->Height = &Height;
	textureInfo->Depth = &Depth;
	textureInfo->MipMapLevels = &MipMapLevels;

	textureInfo->ImGuiDescriptorSet = &ImGuiDescriptorSet;
	textureInfo->Image = &Image;
	textureInfo->Memory = &Memory;
	textureInfo->View = &View;
	textureInfo->Sampler = &Sampler;

	textureInfo->TextureUsage = &TextureUsage;
	textureInfo->TextureType = &TextureType;
	textureInfo->TextureByteFormat = &TextureByteFormat;
	textureInfo->TextureImageLayout = &TextureImageLayout;
	textureInfo->SampleCount = &SampleCount;
	return textureInfo;
}

void Texture::ImGuiShowTexture(const ImVec2& TextureDisplaySize)
{
	ImGui::Image(ImGuiDescriptorSet, TextureDisplaySize);
}