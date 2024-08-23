#include "CShaderCompiler.h"
#include "Global.h"

VkPipelineShaderStageCreateInfo Shader_CreateShader(VkShaderModule shaderModule, VkShaderStageFlagBits shaderStages)
{
    VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = shaderStages,
        .module = shaderModule,
        .pName = "main"
    };

    return pipelineShaderStageCreateInfo;
}

VkShaderModule Shader_CompileGLSLShaderFile(const char* path)
{
    FileState file = File_Read(path);

    VkShaderModuleCreateInfo shaderModuleCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = file.Size,
        .pCode = (uint32_t)file.Data,
    };

    VkShaderModule shaderModule = VK_NULL_HANDLE;
    VkResult result = vkCreateShaderModule(global.Renderer.Device, &shaderModuleCreateInfo, NULL, &shaderModule);
    if (result != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to create shader module: \nFilePath: %s\n Error%s\n", path, result);
    }

    return shaderModule;
}