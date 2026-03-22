// ============================================================
// Lección 1: Primera ventana OpenGL con GLUT
// Dibuja un triángulo RGB en el centro de la pantalla
// ============================================================

#include <GL/glut.h>   // Incluye OpenGL + GLUT juntos

// ----------------------------------------------------------------
// FUNCIÓN DE DISPLAY: Se llama cada vez que hay que redibujar
// ----------------------------------------------------------------
void display() {
    // Paso 1: Limpiar el buffer de color (borrar frame anterior)
    // GL_COLOR_BUFFER_BIT indica que limpiamos los colores
    glClear(GL_COLOR_BUFFER_BIT);

    // Paso 2: Indicar QUÉ vamos a dibujar
    // GL_TRIANGLES = cada 3 vértices forman un triángulo
    glBegin(GL_TRIANGLES);

        // Cada vértice tiene un COLOR y una POSICIÓN
        // glColor3f(R, G, B) → valores entre 0.0 y 1.0
        // glVertex2f(x, y)   → coordenadas en espacio [-1, 1]

        glColor3f(1.0f, 0.0f, 0.0f);  // Rojo
        glVertex2f(0.0f,  0.5f);       // Vértice superior (centro-arriba)

        glColor3f(0.0f, 1.0f, 0.0f);  // Verde
        glVertex2f(-0.5f, -0.5f);      // Vértice inferior izquierdo

        glColor3f(0.0f, 0.0f, 1.0f);  // Azul
        glVertex2f(0.5f, -0.5f);       // Vértice inferior derecho

    glEnd();  // Fin del grupo de primitivas

    // Paso 3: Mostrar lo dibujado (intercambiar buffers)
    // glutSwapBuffers mueve el buffer trasero al frente
    glutSwapBuffers();
}

// ----------------------------------------------------------------
// FUNCIÓN DE RESHAPE: Se llama cuando la ventana cambia de tamaño
// ----------------------------------------------------------------
void reshape(int width, int height) {
    // Decirle a OpenGL el nuevo tamaño del viewport (área de dibujo)
    // x=0, y=0 desde la esquina inferior izquierda
    glViewport(0, 0, width, height);
}

// ----------------------------------------------------------------
// MAIN: Configuración e inicio del programa
// ----------------------------------------------------------------
int main(int argc, char** argv) {
    // 1. Inicializar GLUT con los argumentos del programa
    glutInit(&argc, argv);

    // 2. Configurar el modo de display:
    //    GLUT_DOUBLE = doble buffer (elimina parpadeos)
    //    GLUT_RGB    = colores en formato RGB
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // 3. Definir tamaño inicial de la ventana (ancho x alto en píxeles)
    glutInitWindowSize(800, 600);

    // 4. Definir posición de la ventana en el escritorio (x, y)
    glutInitWindowPosition(100, 100);

    // 5. Crear la ventana con un título
    glutCreateWindow("Mi Primera Ventana OpenGL");

    // 6. Definir el color de fondo al limpiar (R, G, B, Alpha)
    //    0.1, 0.1, 0.1 = gris muy oscuro (casi negro)
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // 7. Registrar los callbacks (funciones que GLUT llamará)
    glutDisplayFunc(display);   // ¿Qué hacer cuando hay que dibujar?
    glutReshapeFunc(reshape);   // ¿Qué hacer si la ventana cambia?

    // 8. Entrar al bucle principal (loop infinito de GLUT)
    //    Este punto NUNCA retorna hasta que cierras la ventana
    glutMainLoop();

    return 0;
}