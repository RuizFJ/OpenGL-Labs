#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Callback para ajustar el área de dibujo si se cambia el tamaño de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Procesar entrada de teclado (Esc para salir)
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Shaders escritos en GLSL
const char* vertexShaderSource = "#version 400 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform float xOffset;\n" // Variable para mover el cuadrado
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 400 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n" // Color Rojo (RGBA)
    "}\n\0";

int main() {
    // 1. Inicializar GLFW
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Crear Ventana
    GLFWwindow* window = glfwCreateWindow(800, 600, "Cuadrado Movil Rojo", NULL, NULL);
    if (window == NULL) {
        std::cout << "Fallo al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1); // ACTIVAR V-SYNC: Movimiento fluido a 60fps (o frecuencia del monitor)

    // 3. Cargar GLAD (Carga las funciones de OpenGL)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Fallo al inicializar GLAD" << std::endl;
        return -1;
    }

    // 4. Compilar y enlazar Shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 5. Definir la geometría del cuadrado (2 triángulos)
    float vertices[] = {
         0.1f,  0.1f, 0.0f,  // Arriba derecha
         0.1f, -0.1f, 0.0f,  // Abajo derecha
        -0.1f, -0.1f, 0.0f,  // Abajo izquierda
        -0.1f,  0.1f, 0.0f   // Arriba izquierda 
    };
    unsigned int indices[] = {
        0, 1, 3,  // Primer triángulo
        1, 2, 3   // Segundo triángulo
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 6. Lógica de animación
    float xOffset = 0.0f;
    float speed = 0.005f; // VELOCIDAD REDUCIDA: Para un movimiento más pausado
    int direction = 1; // 1 = derecha, -1 = izquierda

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Actualizar posición
        xOffset += speed * direction;
        if (xOffset > 0.9f || xOffset < -0.9f) direction *= -1;

        // Renderizado
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Fondo gris oscuro
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        // Enviar la posición actual al shader
        int xOffsetLocation = glGetUniformLocation(shaderProgram, "xOffset");
        glUniform1f(xOffsetLocation, xOffset);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Limpieza
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
