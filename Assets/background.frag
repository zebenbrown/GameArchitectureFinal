#version 330 core

in vec2 textureCoordinates;
out vec4 FragColor;

uniform sampler2D uniformTexture;
uniform float uniformTime;

void main()
{
    float speed = 0.25;
    vec2 uv = textureCoordinates;
    uv.y += fract(uniformTime * speed);

    FragColor = texture(uniformTexture, uv);
}