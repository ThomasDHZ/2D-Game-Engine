#pragma once
extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
}
#include <string>
#include <CShaderCompiler.h>

class ShaderCompiler
{
private:
public:
	static void SetUpCompiler();
	static VkShaderModule CompileGLSLShaderFile(const char* path);
	static VkPipelineShaderStageCreateInfo CreateShader(VkShaderModule& shaderModule, VkShaderStageFlagBits& shaderStages);
	//static Microsoft::WRL::ComPtr<IDxcBlob> BuildShader(const std::string filename, VkShaderStageFlagBits stage);
};

