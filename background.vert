#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoords;

out vec2 v_texCoord;



void main()
{
    v_texCoord = texCoords;

    gl_Position = vec4(position);
}