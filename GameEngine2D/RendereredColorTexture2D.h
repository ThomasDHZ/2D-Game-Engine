#pragma once
#include "Texture.h"

class RendereredColorTexture2D : public Texture
{
private:
protected:
	virtual void CreateTextureSampler() override;
public:
	RendereredColorTexture2D();
	RendereredColorTexture2D(glm::ivec2& textureResolution, VkFormat format);
	virtual ~RendereredColorTexture2D() override;
};

