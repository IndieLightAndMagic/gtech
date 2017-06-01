#version 330 core
out vec4 frgClr;
in vec3 ourColor;

void main()
{

    frgClr = vec4(ourColor, 1.0f);
}