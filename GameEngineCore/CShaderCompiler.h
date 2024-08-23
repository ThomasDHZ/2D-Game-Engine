#include <vulkan/vulkan.h>
#include "io.h"

VkShaderModule Shader_BuildGLSLShaderFile(const char* path);
VkPipelineShaderStageCreateInfo Shader_CreateShader(VkShaderModule shaderModule, VkShaderStageFlagBits shaderStages);