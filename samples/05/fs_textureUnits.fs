#version 330 core
out vec4 xFragColor;
in	vec2 TexCoord; 
in 	vec3 ourColor;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    xFragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.4);
}