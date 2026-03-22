#include <GL/freeglut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);

    glcolor3f(1.0f, 0.0f, 0.0f);
    glVertex2d(0.0f, 0.5f);

    glColor3f(0.0f,1.0f,0.0f);
    glVertex2d(-0.5f,-0.5f);

    glColor3f(0.0f,0.0f,1.0f);
    glVertex2d(0.5f,-0.5f);

    glEnd();

    glutSwapBuffers();
}

// FUNCIÓN DE RESHAPE: Se llama cuando la ventana cambia de tamaño
// ----------------------------------------------------------------
void reshape(int width, int height) {
    // Decirle a OpenGL el nuevo tamaño del viewport (área de dibujo)
    // x=0, y=0 desde la esquina inferior izquierda
    glViewport(0, 0, width, height);
}

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