#pragma once
#include "RenderPass.h"

class RenderPass2D : public RenderPass
{
	private:

	public:
		RenderPass2D();
		~RenderPass2D();
		void BuildRenderPass() override;
		void Destroy() override;
};
