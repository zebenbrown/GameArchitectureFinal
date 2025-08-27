#version 330 core

in vec2 v_texCoord;
out vec4 FragColor;

uniform sampler2D uniformTexture;
//uniform float uniformTime;

void main()
{
   //float speed = 0.25;
   //vec2 uv = v_texCoord;
   //uv.y += fract(uv.y * speed);

    //FragColor = texture(uniformTexture, uv);
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}