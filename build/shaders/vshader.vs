#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 uniModel;
uniform mat4 uniView;
uniform mat4 uniProjection;

void main()
{
    texCoord = inTexCoord;
    gl_Position = uniProjection * uniView * uniModel * vec4(inPos, 1.0f);
}
