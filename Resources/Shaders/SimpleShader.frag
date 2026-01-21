#version 460 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D u_texture;

void main()
{
    //FragColor = vec4(1.0, 1.0, 1.0, 1.0);

    FragColor = texture(u_texture, TexCoord);
}
