#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable
#extension GL_EXT_scalar_block_layout : enable
#extension GL_EXT_debug_printf : enable

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aColor;

layout(location = 0) out vec3 FragPos;
layout(location = 1) out vec2 UV;
layout(location = 2) out vec3 Color;

layout(push_constant) uniform SceneDataBuffer
{
    int	   MeshIndex;
	mat4 Projection;
	mat4 View;
	vec3 CameraPosition;
}sceneData;

struct MeshProperitiesBuffer
{
	int	   MeshIndex;
	int	   MaterialIndex;
	mat4   MeshTransform;
};

layout(binding = 0) buffer MeshProperities { MeshProperitiesBuffer meshProperties; } meshBuffer[];

void main() 
{
    mat4 MeshTransform = meshBuffer[0].meshProperties.MeshTransform;
    FragPos = vec3(inPosition.xy, 0.0f);    
    Color = aColor;
    UV = aUV;
    gl_Position = sceneData.Projection * 
                  sceneData.View *   
                  vec4(inPosition, 0.0f, 1.0f);
}