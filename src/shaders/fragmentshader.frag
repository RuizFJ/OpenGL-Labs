// fragmentshader.frag
#version 400 core
in vec3 ourColor;   // llega interpolado automáticamente
out vec4 FragColor;

void main() {
    FragColor = vec4(ourColor, 1.0);
}