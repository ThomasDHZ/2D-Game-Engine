#pragma once
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

