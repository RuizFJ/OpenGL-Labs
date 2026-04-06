#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>
#include "OpenGL/shaderProgram.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

// Resuelve rutas relativas a partir del directorio del ejecutable.
// Necesario en Windows para que los shaders se encuentren sin importar
// desde dónde se lance el programa.
std::string getExeDir() {
#ifdef _WIN32
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string exePath(path);
    return exePath.substr(0, exePath.find_last_of("\\/") + 1);
#else
    return "";
#endif
}

// Se llama automáticamente cuando la ventana cambia de tamaño.
// Ajusta el viewport para que OpenGL siga usando toda la ventana.
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(){

    // ─── INICIALIZACIÓN ───────────────────────────────────────────────────────

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // Core Profile: sin funciones legacy (glBegin, glVertex, glColor, etc.)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD carga las direcciones reales de las funciones de OpenGL en tiempo
    // de ejecución. Debe llamarse antes de cualquier función gl*.
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ─── DATOS DE VÉRTICES ────────────────────────────────────────────────────

    // Cada vértice tiene 6 floats: posición (X, Y, Z) + color (R, G, B)
    float vertices[] = {
        // X      Y      Z      R     G     B
         0.5f, -0.5f,  0.0f,  1.0f, 0.0f, 0.0f,  // inferior derecho  - rojo
        -0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  // inferior izquierdo - verde
         0.0f,  0.5f,  0.0f,  0.0f, 0.0f, 1.0f   // superior centro    - azul
    };

    // ─── BUFFERS EN GPU ───────────────────────────────────────────────────────

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // El VAO graba toda la configuración de atributos que se haga mientras
    // está activo. Al hacer Bind en el render loop, restaura esa configuración.
    glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Atributo 0 → layout(location = 0) en el vertex shader → posición
        // stride = 6*sizeof(float): tamaño completo de un vértice en bytes
        // offset = 0: la posición empieza al inicio de cada vértice
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Atributo 1 → layout(location = 1) en el vertex shader → color
        // offset = 3*sizeof(float): el color empieza después de X, Y, Z
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Desvincula el VAO para no modificarlo accidentalmente

    // ─── SHADERS ──────────────────────────────────────────────────────────────

    std::string exeDir = getExeDir();
    ShaderProgram shaderProgram(
        exeDir + "shaders/vertexshader.vert",
        exeDir + "shaders/fragmentshader.frag"
    );

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shaderProgram.use();

    // ─── RENDER LOOP ──────────────────────────────────────────────────────────

    while(!glfwWindowShouldClose(window)){

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Uniform: valor que se envía desde CPU a shader, igual para todos
        // los vértices. Aquí anima el color con una onda sinusoidal.
        shaderProgram.setFloat("mivariable", sinf((float)glfwGetTime()));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        processInput(window);
        glfwSwapBuffers(window); // Muestra el frame renderizado
        glfwPollEvents();
    }

    // ─── LIMPIEZA ─────────────────────────────────────────────────────────────

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    shaderProgram.deleteprogram();
    glfwTerminate();
    return 0;
}