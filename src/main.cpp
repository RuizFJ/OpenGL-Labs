#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>
#include "OpenGL/shaderProgram.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

// Obtiene el directorio donde está el ejecutable para resolver rutas relativas
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(800,600, "LearnOpenGL", NULL,NULL);

    if(window == NULL){
        std::cout <<"Failed to create GLFW Window" <<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    //En este parte de codigo, se cargan las funciones de OpenGL utilizando GLAD, que es un cargador de funciones de OpenGL. 
    //La función gladLoadGLLoader toma como argumento una función que se utiliza para obtener la dirección de las funciones de OpenGL. 
    //En este caso, se utiliza glfwGetProcAddress, que es una función proporcionada por GLFW para obtener la dirección de las funciones de OpenGL.
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout <<"Failed to initialize GLAD" <<std::endl;
        return -1;
    }

    //* 1.- Mandamos informacion a la GPU

    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    //En esta parte del código, se genera un buffer de vértices (VBO) utilizando la función glGenBuffers.
    //! Si o si va despues de gladLoadGLLoader, porque es una función de OpenGL y necesita que las funciones de OpenGL estén cargadas para poder ser utilizada.
    unsigned int VBO;
    unsigned int VAO; //Vertex Array Object

    unsigned int EBO; //Element Buffer Object

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO); //se vincula el VAO para que las siguientes llamadas a funciones de OpenGL afecten a este VAO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);  //se genera un buffer de vértices (VBO) y un buffer de elementos (EBO) utilizando la función glGenBuffers. El VBO se utiliza para almacenar los datos de los vértices, mientras que el EBO se utiliza para almacenar los índices que definen cómo se deben dibujar los vértices.

    //Luego, se vincula el buffer de vértices al objetivo GL_ARRAY_BUFFER utilizando la función glBindBuffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //se vincula el buffer de elementos al objetivo GL_ELEMENT_ARRAY_BUFFER utilizando la función glBindBuffer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //se copia la información de los índices al buffer de elementos utilizando la 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //se habilita el atributo de vértice 0 para que OpenGL pueda usarlo al renderizar
    glBindVertexArray(0); //se desvincula el VAO para evitar modificarlo accidentalmente en el futuro

    //* Crear shader program usando archivos externos
    // Se usa la clase ShaderProgram que lee los archivos .vert y .frag desde disco
    // getExeDir() obtiene la carpeta del .exe para que las rutas funcionen sin importar desde dónde se ejecute
    std::string exeDir = getExeDir();
    ShaderProgram shaderProgram(exeDir + "shaders/vertexshader.vert", exeDir + "shaders/fragmentshader.frag");

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // MODO ALAMBRE: Dibuja solo los bordes de los triángulos
    
    shaderProgram.use();
    //glUniform1f(location, 0.5f); para mandar un valor a la variable uniforme "mivariable" en el shader. En este caso, se le asigna el valor 0.5f.
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        shaderProgram.setFloat("mivariable", sinf(timeValue));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 6); //Dibuja los triángulos utilizando los vértices en el orden en que fueron definidos en el buffer de vértices. El segundo argumento es el índice del primer vértice a dibujar, y el tercer argumento es el número de vértices a dibujar. En este caso, se dibujan 6 vértices (2 triángulos) comenzando desde el índice 0.
        //glBindVertexArray(0);


        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    shaderProgram.deleteprogram();
    glfwTerminate();
    return 0;
}