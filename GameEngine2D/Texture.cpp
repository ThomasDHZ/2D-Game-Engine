#include "Texture.h"
extern "C"
{
	#define STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_WRITE_IMPLEMENTATION
	
	#include <io.h>
	#include <stb_image.h>
}

Texture::Texture()
{
	void* image = (char*)"adsfdasfasdfasdf";
	VulkanBuffer buffer(image, sizeof(image), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
}

Texture::Texture(int a)
{
	void* image = (char*)"adsfdasfasdfasdf";
	VulkanBuffer buffer(image, sizeof(image), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
}

Texture::Texture(const TextureInfo& textureLoader)
{
	void* image = (char*)"adsfdasfasdfasdf";
	VulkanBuffer buffer(image, sizeof(image), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

}

TextureInfo* Texture::SendCTextureInfo()
{
	TextureInfo CTextureInfo =
	{
		.Width = &Width,
		.Height = &Height,
		.Depth = &Depth,
		.MipMapLevels = &MipMapLevels,
		.TextureUsage = &TextureUsage,
		.TextureType = &TextureType,
		.TextureByteFormat = &TextureByteFormat,
		.TextureImageLayout = &TextureImageLayout,
		.SampleCount = &SampleCount,
	};
	return &CTextureInfo;
}

void Texture::LoadTexture(const std::string& FilePath)
{
	//MipMapLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(textureLoader.TextureLoader.width, textureLoader.TextureLoader.height)))) + 1;

	int width = 0;
	int height = 0;
	int colorChannels = 0;
	unsigned char* data = stbi_load(FilePath.c_str(), &width, &height, &colorChannels, 0);
	VulkanBuffer buffer(data, sizeof(data), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	Texture_CreateTextureImage(SendCTextureInfo());
	Texture_TransitionImageLayout(SendCTextureInfo(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Texture_CopyBufferToTexture(SendCTextureInfo(), &buffer.Buffer);
	Texture_GenerateMipmaps(SendCTextureInfo());
}
