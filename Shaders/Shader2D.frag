#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable
#extension GL_EXT_scalar_block_layout : enable
#extension GL_EXT_debug_printf : enable

layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 UV;
layout(location = 2) in vec3 Color;

layout(location = 0) out vec4 outColor;

void main() 
{
//
//	MaterialProperties material = materialBuffer[sceneData.MaterialIndex].materialProperties;
//	material.Albedo = texture(TextureMap[material.AlbedoMap], UV).rgb;
//	material.Alpha = texture(TextureMap[material.AlbedoMap], UV).a;
//	
//	if(material.Alpha != 1.0f)
//	{
//		discard;
//	}
//
//   vec3 result = material.Albedo;
//   
//   vec3 finalResult = vec3(1.0) - exp(-result * 1.0f);
//		finalResult = pow(finalResult, vec3(1.0 / 2.2f));
//
//   outColor = vec4(finalResult,1.0f);
}