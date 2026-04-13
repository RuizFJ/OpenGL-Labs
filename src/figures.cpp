#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <iostream> 
#include <string>

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Fallo al compilar el sombreado: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

int main(void) {
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(800, 600, "Mi primera pantalla en OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) std::cout << "Error en GLEW!" << std::endl;

    // --- DEFINICIÓN DE VÉRTICES ---
    // Agrupamos todos los vértices en un solo arreglo para facilitar el manejo
    float vertices[] = {
        // 1. OCTÁGONO (Cuadrante Superior Derecho)
         0.4f,  0.8f,   0.6f,  0.8f,   0.8f,  0.6f,   0.8f,  0.4f,
         0.6f,  0.2f,   0.4f,  0.2f,   0.2f,  0.4f,   0.2f,  0.6f,

         // 2. PENTÁGONO (Cuadrante Superior Izquierdo)
         -0.5f,  0.9f,  -0.2f,  0.6f,  -0.3f,  0.2f,  -0.7f,  0.2f,  -0.8f,  0.6f,

         // 3. HEXÁGONO (Cuadrante Inferior Izquierdo)
         -0.5f, -0.2f,  -0.2f, -0.4f,  -0.2f, -0.7f,  -0.5f, -0.9f,  -0.8f, -0.7f,  -0.8f, -0.4f,

         // 4. ESTRELLA / CRUZ (Cuadrante Inferior Derecha - 8 vértices para forma de diamante/estrella)
          0.5f, -0.2f,   0.6f, -0.5f,   0.9f, -0.5f,   0.6f, -0.6f,   0.5f, -0.9f,   0.4f, -0.6f,   0.1f, -0.5f,   0.4f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // Shaders
    std::string vertexShader =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main() { gl_Position = position; }\n";

    std::string fragmentShader =
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "uniform vec4 u_Color;\n" // Uniform para cambiar color dinámicamente
        "void main() { color = u_Color; }\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    // Obtener la localización del uniform del color
    int location = glGetUniformLocation(shader, "u_Color");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 1. Dibujar OCTÁGONO (Amarillo) - 8 vértices, empieza en index 0
        glUniform4f(location, 1.0f, 1.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 8);

        // 2. Dibujar PENTÁGONO (Verde) - 5 vértices, empieza en index 8
        glUniform4f(location, 0.0f, 1.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 8, 5);

        // 3. Dibujar HEXÁGONO (Celeste) - 6 vértices, empieza en index 13
        glUniform4f(location, 0.0f, 0.8f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 13, 6);

        // 4. Dibujar ESTRELLA/CRUZ (Rosado) - 8 vértices, empieza en index 19
        glUniform4f(location, 1.0f, 0.0f, 0.3f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 19, 8);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}