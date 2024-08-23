#pragma once
extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
	#include <io.h>
}
#include <string>
#include <CShaderCompiler.h>
#include "HLSLShaderCompiler.h"

class ShaderCompiler
{
private:
	static Microsoft::WRL::ComPtr<IDxcUtils> dxc_utils;
	static Microsoft::WRL::ComPtr<IDxcCompiler3> dxc_compiler;
	static Microsoft::WRL::ComPtr<IDxcIncludeHandler> DefaultIncludeHandler;

	static std::string ConvertLPCWSTRToString(LPCWSTR lpcwszStr);
	static void uint32ToUnsignedCharString(uint32_t value, std::string& string);
public:
	static void SetUpCompiler();
	static VkShaderModule CompileGLSLShaderFile(const char* path);
	static Microsoft::WRL::ComPtr<IDxcBlob> CompileHLSLShaderFile(const std::string filename, VkShaderStageFlagBits stage);
	static VkPipelineShaderStageCreateInfo CreateShader(VkShaderModule& shaderModule, VkShaderStageFlagBits shaderStages);
};

