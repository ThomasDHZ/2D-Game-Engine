#pragma once
#include "VulkanRenderer.h"

enum TextureUsageEnum 
{
    kUse_Undefined,
    kUse_2DImageTexture,
    kUse_2DDataTexture,
    kUse_2DDepthTexture,
    kUse_3DImageTexture,
    kUse_3DDataTexture,
    kUse_3DDepthTexture,
    kUse_CubeMapTexture,
    kUse_CubeMapDepthTexture
};

enum TextureTypeEnum 
{
    kType_UndefinedTexture,
    kType_TextureAtlas,
    kType_RenderedColorTexture,
    kType_RenderedDepthTexture,
    kType_ReadableTexture,
    kType_DiffuseTextureMap,
    kType_SpecularTextureMap,
    kType_AlbedoTextureMap,
    kType_MetallicTextureMap,
    kType_RoughnessTextureMap,
    kType_AmbientOcclusionTextureMap,
    kType_NormalTextureMap,
    kType_DepthTextureMap,
    kType_AlphaTextureMap,
    kType_EmissionTextureMap,
    kType_PaletteRotationMap,
    kType_CubeMapTexture,
    kType_CubeMapDepthTexture,
    kType_EnvironmentTexture,
    kType_RenderedCubeMap,
    kType_BakedTexture
};

typedef struct TextureInfo 
{
    int* Width;
    int* Height;
    int* Depth;
    uint32_t* MipMapLevels;

    VkDescriptorSet* ImGuiDescriptorSet;
    VkImage* Image;
    VkDeviceMemory* Memory;
    VkImageView* View;
    VkSampler* Sampler;

    enum TextureUsageEnum* TextureUsage;
    enum TextureTypeEnum* TextureType;
    VkFormat* TextureByteFormat;
    VkImageLayout* TextureImageLayout;
    VkSampleCountFlagBits* SampleCount;
};

void Texture_CreateTextureImage(struct TextureInfo* textureInfo);
void Texture_TransitionImageLayout(struct TextureInfo* textureInfo, VkImageLayout imageLayout);
void Texture_CopyBufferToTexture(struct TextureInfo* textureInfo, VkBuffer* buffer);
void Texture_GenerateMipmaps(struct TextureInfo* textureInfo);
VkResult Texture_CreateTextureView(struct TextureInfo* textureInfo, VkImageViewCreateInfo* imageViewCreateInfo);
VkResult Texture_CreateTextureSampler(struct TextureInfo* textureInfo, VkSamplerCreateInfo* samplerCreateInfo);