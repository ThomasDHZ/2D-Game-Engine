#include "ShaderCompiler.h"

VkShaderModule ShaderCompiler::CompileGLSLShaderFile(const char* path)
{
	return Shader_CompileGLSLShaderFile(path);
}

VkPipelineShaderStageCreateInfo ShaderCompiler::CreateShader(VkShaderModule& shaderModule, VkShaderStageFlagBits& shaderStages)
{
	return Shader_CreateShader(shaderModule, shaderStages);
}
