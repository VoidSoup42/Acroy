#version 460 core

out vec4 fragColor;
in vec2 texCoord;
in vec3 color;

uniform sampler2D u_texture;

void main()
{
    // fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    // fragColor = texture(u_texture, texCoord);
    fragColor = vec4(color, 1.0);
}
