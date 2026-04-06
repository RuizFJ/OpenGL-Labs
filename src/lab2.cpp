#include <GLFW/glfw3.h> 

#include <cmath> 

 // this code uses legacy OpenGL functions (glBegin, glVertex, etc.) for simplicity.

void drawRectangle(float x, float y, float width, float height, float r, float g, float b) { 

    glColor3f(r, g, b); 

    glBegin(GL_QUADS); 

    glVertex2f(x, y); 

    glVertex2f(x + width, y); 

    glVertex2f(x + width, y - height); 

    glVertex2f(x, y - height); 

    glEnd(); 

} 

 

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) { 

    glColor3f(r, g, b); 

    glBegin(GL_TRIANGLES); 

    glVertex2f(x1, y1); 

    glVertex2f(x2, y2); 

    glVertex2f(x3, y3); 

    glEnd(); 

} 

 

void drawCircle(float cx, float cy, float r, int num_segments) { 

    glBegin(GL_TRIANGLE_FAN); 

    glColor3f(1.0f, 1.0f, 0.0f); // Amarillo 

    glVertex2f(cx, cy); 

    for (int i = 0; i <= num_segments; i++) { 

        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); 

        float x = r * cosf(theta); 

        float y = r * sinf(theta); 

        glVertex2f(x + cx, y + cy); 

    } 

    glEnd(); 

} 

 

void drawSun(float x, float y, float radius) { 

    drawCircle(x, y, radius, 100); 

 

    // Dibujar los rayos del sol 

    float rayLength = radius * 1.5f; 

    for (int i = 0; i < 8; i++) { 

        float angle = i * 3.1415926f / 4.0f; 

        float x1 = x + cos(angle) * radius; 

        float y1 = y + sin(angle) * radius; 

        float x2 = x + cos(angle) * rayLength; 

        float y2 = y + sin(angle) * rayLength; 

        glColor3f(1.0f, 1.0f, 0.0f); 

        glBegin(GL_LINES); 

        glVertex2f(x1, y1); 

        glVertex2f(x2, y2); 

        glEnd(); 

    } 

} 

 

void drawHouse(float x, float y, float width, float height) { 

    // Cuerpo de la casa 

    drawRectangle(x, y, width, height, 0.6f, 0.3f, 0.0f); // Marrón 

 

    // Techo 

    drawTriangle(x - 0.05f, y, x + width + 0.05f, y, x + width / 2, y + height * 0.6f, 0.8f, 0.0f, 0.0f); // Rojo 

 

    // Puerta 

    drawRectangle(x + width * 0.4f, y - height * 0.6f, width * 0.2f, height * 0.6f, 0.4f, 0.2f, 0.0f); // Marrón oscuro 

} 

 

int main(void) 

{ 

    GLFWwindow* window; 

 

    if (!glfwInit()) 

        return -1; 

 

    window = glfwCreateWindow(1800, 1080, "Lab PG1", NULL, NULL); 

    if (!window) 

    { 

        glfwTerminate(); 

        return -1; 

    } 

 

    glfwMakeContextCurrent(window); 

 

    while (!glfwWindowShouldClose(window)) 

    { 

        glClear(GL_COLOR_BUFFER_BIT); 

 

        // **Primera figura - Bandera de Portugal 

        float width = 0.3f, height = 0.2f, offsetX = -0.9f, offsetY = 0.9f; 

 

        // Mitad izquierda - Verde 

        drawRectangle(offsetX, offsetY, width / 2, height, 0.0f, 1.0f, 0.0f); 

 

        // Mitad derecha - Roja 

        drawRectangle(offsetX + width / 2, offsetY, width / 2, height, 1.0f, 0.0f, 0.0f); 

 

        // Círculo amarillo en el centro 

        float circleX = offsetX + width / 2; 

        float circleY = offsetY - height / 2; 

        drawCircle(circleX, circleY, 0.05f, 100); 

 

        // **Segunda figura - Cara de GD 

        width = 0.2f; 

        height = 0.2f; 

        offsetX = -0.9f; 

        offsetY = 0.2f; 

 

        // Cuadrado principal (cara) 

        drawRectangle(offsetX, offsetY, width, height, 0.5f, 0.5f, 0.5f); 

 

        // Extensión inferior 

        drawRectangle(offsetX + width * 0.25f, offsetY - height, width * 0.5f, height * 0.25f, 0.5f, 0.5f, 0.5f); 

 

        // Cuadrado central 

        drawRectangle(offsetX + width * 0.35f, offsetY - height * 0.35f, width * 0.3f, height * 0.3f, 0.0f, 0.0f, 0.0f); 

 

        // **Sol en la esquina superior derecha 

        drawSun(0.8f, 0.8f, 0.1f); 

 

        // **Casa en la esquina inferior derecha 

        drawHouse(0.5f, -0.6f, 0.3f, 0.3f); 

 

        glfwSwapBuffers(window); 

        glfwPollEvents(); 

    } 

 

    glfwTerminate(); 

    return 0; 

} 