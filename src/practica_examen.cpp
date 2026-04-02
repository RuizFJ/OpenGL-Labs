// ============================================================
//  PRACTICA DE EXAMEN - OpenGL: Shaders y Buffers
//  Basado en el programa main.cpp del curso
// ============================================================
//
//  INSTRUCCIONES:
//  Completa los espacios marcados con TODO y responde las
//  preguntas en los comentarios. Luego compila y verifica
//  que el programa renderiza correctamente.
//
//  OBJETIVO: Dibujar dos triángulos que forman un rectángulo
//  usando VBO, VAO, EBO y un shader program básico.
// ============================================================

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ============================================================
// PREGUNTA 1: ¿Para qué sirve este callback?
// ¿Cuándo es llamado automáticamente por GLFW?
// ============================================================
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // TODO: llama a la función correcta de OpenGL para ajustar
    // el viewport al nuevo tamaño de la ventana
    // glViewport(???, ???, ???, ???);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// ============================================================
// PREGUNTA 2: ¿Qué hace layout (location = 0)?
// ¿Cómo se conecta esto con glVertexAttribPointer?
// ============================================================
const char* vertexShaderSource =
    "#version 400 core\n"
    "layout (location = 0) in vec3 aPos;\n"   // <-- atributo de posición
    "void main()\n"
    "{\n"
    // TODO: asigna la posición final del vértice a gl_Position
    // Recuerda: gl_Position espera un vec4(x, y, z, w)
    "   /* gl_Position = ??? */\n"
    "}\0";

// ============================================================
// PREGUNTA 3: ¿Qué significa 'out vec4 FragColor'?
// ¿Qué representa cada componente del vec4 del color abajo?
// ============================================================
const char* fragmentShaderSource =
    "#version 400 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    // TODO: asigna un color naranja al fragmento (R=1.0, G=0.5, B=0.2, A=1.0)
    "   /* FragColor = ??? */\n"
    "}\n\0";

int main() {

    // ----------------------------------------------------------
    // INICIALIZACIÓN DE GLFW
    // ----------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // PREGUNTA 4: ¿Qué hace GLFW_CONTEXT_VERSION_MAJOR/MINOR?

    GLFWwindow* window = glfwCreateWindow(800, 600, "Examen OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ----------------------------------------------------------
    // DATOS DE VÉRTICES E ÍNDICES
    // ----------------------------------------------------------
    // PREGUNTA 5: ¿Por qué usamos índices en lugar de repetir vértices?
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // 0 - top right
         0.5f, -0.5f, 0.0f,  // 1 - bottom right
        -0.5f, -0.5f, 0.0f,  // 2 - bottom left
        -0.5f,  0.5f, 0.0f   // 3 - top left
    };

    unsigned int indices[] = {
        0, 1, 3,  // primer triángulo
        1, 2, 3   // segundo triángulo
    };

    // ----------------------------------------------------------
    // SECCIÓN BUFFERS: VAO, VBO, EBO
    // ----------------------------------------------------------
    // PREGUNTA 6: ¿Cuál es la diferencia entre VAO, VBO y EBO?
    //   VAO = _______________
    //   VBO = _______________
    //   EBO = _______________

    unsigned int VAO, VBO, EBO;

    // TODO: genera 1 VAO, 1 VBO y 1 EBO
    // glGen___(1, &VAO);
    // glGen___(1, &VBO);
    // glGen___(1, &EBO);

    // TODO: vincula el VAO PRIMERO
    // glBind___(VAO);

    // TODO: vincula el VBO al objetivo correcto y sube los datos de vértices
    // glBindBuffer(???, VBO);
    // glBufferData(???, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // TODO: vincula el EBO al objetivo correcto y sube los datos de índices
    // glBindBuffer(???, EBO);
    // glBufferData(???, sizeof(indices), indices, GL_STATIC_DRAW);

    // ----------------------------------------------------------
    // INTERPRETACIÓN DE ATRIBUTOS DE VÉRTICE
    // ----------------------------------------------------------
    // PREGUNTA 7: Explica cada parámetro de glVertexAttribPointer:
    //   glVertexAttribPointer(índice, tamaño, tipo, normalizado, stride, offset)
    //   índice=0  -> _______________
    //   tamaño=3  -> _______________
    //   tipo      -> _______________
    //   stride    -> _______________
    //   offset    -> _______________

    // TODO: configura el atributo de vértice 0 (posición)
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // TODO: habilita el atributo de vértice 0
    // glEnable___(0);

    // TODO: desvincula el VAO para evitar modificaciones accidentales
    // glBindVertexArray(???);

    // ----------------------------------------------------------
    // COMPILACIÓN DE SHADERS
    // ----------------------------------------------------------
    // PREGUNTA 8: ¿Cuáles son los pasos para compilar y enlazar shaders?
    // Ordena: glLinkProgram, glCompileShader, glCreateShader,
    //         glCreateProgram, glShaderSource, glAttachShader

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // TODO: carga el código fuente en el shader
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // TODO: compila el vertex shader
    // glCompile___(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // TODO: repite los dos pasos anteriores para el fragment shader

    // Verificación de errores (ya implementada para ti - ¡no ignores los errores!)
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ----------------------------------------------------------
    // SHADER PROGRAM (enlace de shaders)
    // ----------------------------------------------------------
    // PREGUNTA 9: ¿Por qué se eliminan los shaders individuales
    // después de enlazarlos al programa?

    unsigned int shaderProgram = glCreateProgram();
    // TODO: adjunta vertex y fragment shader al programa
    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);
    // TODO: enlaza (link) el programa
    // glLink___(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // TODO: elimina los shaders individuales (ya no los necesitamos)
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);

    // Registrar el callback de redimensionado
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // PREGUNTA 10: ¿Qué diferencia hay entre GL_FILL y GL_LINE en glPolygonMode?
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Modo alambre

    // ----------------------------------------------------------
    // RENDER LOOP
    // ----------------------------------------------------------
    // TODO: activa el shader program antes del loop
    // glUse___(shaderProgram);

    while (!glfwWindowShouldClose(window)) {
        // Color de fondo (R=0.2, G=0.3, B=0.3, A=1.0)
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: vincula el VAO
        // glBindVertexArray(???);

        // PREGUNTA 11: ¿Cuál es la diferencia entre glDrawArrays y glDrawElements?
        // ¿Cuándo usarías cada uno?

        // TODO: dibuja usando índices (EBO), 6 índices, tipo unsigned int
        // glDrawElements(GL_TRIANGLES, ???, GL_UNSIGNED_INT, 0);

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ----------------------------------------------------------
    // LIMPIEZA
    // ----------------------------------------------------------
    // PREGUNTA 12: ¿Por qué es importante limpiar los recursos de GPU?
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

// ============================================================
//  RESPUESTAS (para autoevaluar después de completar el código)
// ============================================================
/*
1. framebuffer_size_callback: Se llama cuando la ventana cambia de tamaño.
   Ajusta el viewport para que OpenGL sepa el nuevo área de renderizado.
   -> glViewport(0, 0, width, height);

2. layout(location=0): Define que el atributo 'aPos' está en la posición
   de atributo 0. Se conecta con el primer argumento de glVertexAttribPointer(0,...).

3. 'out vec4 FragColor': Variable de salida del fragment shader. Los 4 valores
   son (R, G, B, A) → (Rojo, Verde, Azul, Alfa/Transparencia) en rango [0.0, 1.0].

4. GLFW_CONTEXT_VERSION: Especifica que se usa OpenGL versión 4.0.

5. Índices (EBO): Evitan duplicar vértices compartidos. Un rectángulo tiene 4
   vértices únicos, pero 6 sin EBO (el vértice 1 y 3 se repetirían).

6. VAO = Vertex Array Object: recuerda qué VBOs y atributos pertenecen a un objeto.
   VBO = Vertex Buffer Object: almacena datos de vértices en la GPU.
   EBO = Element Buffer Object: almacena los índices de dibujo.

7. glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0)
   - índice=0: atributo de vértice en location 0 (aPos en el shader)
   - tamaño=3: 3 componentes por vértice (x, y, z)
   - GL_FLOAT: tipo de dato
   - stride=12: bytes entre el inicio de un vértice y el siguiente
   - offset=0: el atributo empieza al inicio del buffer

8. Orden correcto:
   1) glCreateShader  2) glShaderSource  3) glCompileShader
   4) glCreateProgram 5) glAttachShader  6) glLinkProgram

9. Los shaders individuales ya están enlazados en el programa. Eliminarlos
   libera memoria en la GPU (ya no son necesarios).

10. GL_FILL: rellena los triángulos (modo normal).
    GL_LINE: dibuja solo los bordes (modo alambre/wireframe).

11. glDrawArrays: dibuja usando el orden de vertices en el VBO.
    glDrawElements: dibuja usando los índices del EBO (más eficiente con vértices compartidos).

12. Los buffers, VAOs y programas viven en la memoria de la GPU. Si no se
    eliminan, se produce un memory leak de GPU.
*/
