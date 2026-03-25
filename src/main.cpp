#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

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
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top
    };
    //En esta parte del código, se genera un buffer de vértices (VBO) utilizando la función glGenBuffers.
    //! Si o si va despues de gladLoadGLLoader, porque es una función de OpenGL y necesita que las funciones de OpenGL estén cargadas para poder ser utilizada.
    unsigned int VBO;
    unsigned int VAO; //Vertex Array Object

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO); //se vincula el VAO para que las siguientes llamadas a funciones de OpenGL afecten a este VAO
    glGenBuffers(1, &VBO);

    //Luego, se vincula el buffer de vértices al objetivo GL_ARRAY_BUFFER utilizando la función glBindBuffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    //* 2.- Decirle a OpenGL como interpretar los datos de los vértices
    //En esta parte del código, se especifica cómo OpenGL debe interpretar los datos de los vértices utilizando la función glVertexAttribPointer.
    //1- El primer argumento (0) es el índice del atributo de vértice que se va a configurar. En este caso, se está configurando el atributo de vértice 0.
    //2- El segundo argumento (3) es el número de componentes por vértice. En este caso, cada vértice tiene 3 componentes (x, y, z).
    //3- El tercer argumento (GL_FLOAT) es el tipo de datos de cada componente. En este caso, cada componente es un float.
    //4- El cuarto argumento (GL_FALSE) indica si los datos deben ser normalizados. En este caso, no se normalizan.
    //5- El quinto argumento (3*sizeof(float)) es el tamaño en bytes de cada vértice. En este caso, cada vértice tiene 3 componentes de tipo float, por lo que el tamaño es 3 veces el tamaño de un float.
    //6- El sexto argumento ((void*)0) es un puntero a los datos de los vértices. En este caso, los datos de los vértices comienzan en el inicio del buffer, por lo que se pasa un puntero nulo.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //se habilita el atributo de vértice 0 para que OpenGL pueda usarlo al renderizar
    glBindVertexArray(0); //se desvincula el VAO para evitar modificarlo accidentalmente en el futuro
    //* Crear vertex shader y fragment shader

    const char* vertexShaderSource = "#version 400 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 400 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    unsigned int vertexShader;
    unsigned int fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout <<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<infoLog <<std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout <<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<infoLog <<std::endl;
    }

    //* Crear shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout <<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<infoLog <<std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glUseProgram(shaderProgram);
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);


        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}