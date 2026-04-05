#version 400 core

layout (location = 0) in vec3 aPos;

out vec3 ourColor;
uniform float mivariable;

void main()
{
   ourColor = vec3(1.0, 0.5, 0.2);
   gl_Position = vec4(aPos.x + mivariable, aPos.y, aPos.z, 1.0);
}