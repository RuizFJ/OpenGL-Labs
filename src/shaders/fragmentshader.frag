#version 400 core

out vec4 FragColor;
in vec3 ourColor;
uniform float mivariable;

void main()
{
   FragColor = vec4(ourColor, 1.0f);
}