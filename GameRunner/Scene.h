#pragma once
extern "C"
{
#include <Global.h>
#include <VulkanRenderer.h>
}
#include <InterfaceRenderPass.h>
#include "RenderPass2D.h"

class Scene
{
	private:
	public:
		void StartUp();
		void Update();
		void ImGuiUpdate();
		void BuildRenderers();
		void Draw();
		void Destroy();
};

