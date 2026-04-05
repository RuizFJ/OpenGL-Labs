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
    glBindBuffer(GL_ARRAY_BUFFER, VBO);\
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //se vincula el buffer de elementos al objetivo GL_ELEMENT_ARRAY_BUFFER utilizando la función glBindBuffer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //se copia la información de los índices al buffer de elementos utilizando la función glBufferData. El tercer argumento es un puntero a los datos de los índices, y el cuarto argumento indica cómo se deben usar los datos (en este caso, GL_STATIC_DRAW indica que los datos no cambiarán con frecuencia).

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
        "out vec3 ourColor;\n"
        "uniform float mivariable;\n"
        "void main()\n"
        "{\n"
        "   ourColor = vec3(1.0, 0.5, 0.2);\n"
        "   gl_Position = vec4(aPos.x + mivariable, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 400 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "uniform float mivariable;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(ourColor, 1.0f);\n"
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // MODO ALAMBRE: Dibuja solo los bordes de los triángulos
    
    glUseProgram(shaderProgram);
    int location = glGetUniformLocation(shaderProgram, "mivariable");
    //glUniform1f(location, 0.5f); para mandar un valor a la variable uniforme "mivariable" en el shader. En este caso, se le asigna el valor 0.5f.
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        glUniform1f(location, sin(timeValue));

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
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}