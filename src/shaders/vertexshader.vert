// vertexshader.vert
#version 400 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;  // nuevo atributo

out vec3 ourColor;  // se lo pasamos al fragment shader

void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}