#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

#define M_PI 3.14159265358979323846
float cameraX = 3.0f;
float cameraY = 3.0f;
float cameraZ = 5.0f;

void init(void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glEnableClientState (GL_VERTEX_ARRAY);
    glEnableClientState (GL_COLOR_ARRAY);

    

}

GLfloat groundVertices[][3] = {
    {0.0, 0.0, -5.0},   // Vertex 1
    {-5.0, 0.0, 0.0},   // Vertex 2
    {0.0, 0.0, 5.0},   // Vertex 3
    {5.0, 0.0, 0.0}    // Vertex 4
};

void drawHalfSphere(float radius, int slices, int stacks) {
    // Set the color to white
    glColor3f(1.0, 1.0, 1.0);
    
    // Iterate over the stacks
    for (int i = 0; i < stacks; i++) {
        float phi1 = M_PI * i / stacks;
        float phi2 = M_PI * (i + 1) / stacks;

        // Iterate over the slices
        for (int j = 0; j < slices; j++) {
            float theta1 = 2.0 * M_PI * j / slices;
            float theta2 = 2.0 * M_PI * (j + 1) / slices;

            // Calculate the vertices of the quad
            float x1 = radius * sin(phi1) * cos(theta1);
            float y1 = radius * sin(phi1) * sin(theta1);
            float z1 = radius * cos(phi1);

            float x2 = radius * sin(phi1) * cos(theta2);
            float y2 = radius * sin(phi1) * sin(theta2);
            float z2 = radius * cos(phi1);

            float x3 = radius * sin(phi2) * cos(theta2);
            float y3 = radius * sin(phi2) * sin(theta2);
            float z3 = radius * cos(phi2);

            float x4 = radius * sin(phi2) * cos(theta1);
            float y4 = radius * sin(phi2) * sin(theta1);
            float z4 = radius * cos(phi2);

            // Draw the quad using GL_TRIANGLE_FAN
            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);
            glEnd();
        }
    }
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity ();             /* clear the matrix */
    /* viewing transformation  */
    gluLookAt (cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    //Ground Plane
    glColor3f(0.0, 0.8, 1.0);
    // Draw the rectangle
    glBegin(GL_QUADS);
        glVertex3fv(groundVertices[0]);
        glVertex3fv(groundVertices[1]);
        glVertex3fv(groundVertices[2]);
        glVertex3fv(groundVertices[3]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -2.0, 0.0);
    drawHalfSphere(2.0, 20, 10);
    glPopMatrix();


    glFlush();
}


void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27: // Escape key
            exit(0);
            break;
        case 'x':
            // Move left (decrease x position)
            cameraX -= 0.1f;
            glutPostRedisplay();
            break;
        case 'X':
            // Move right (increase x position)
            cameraX += 0.1f;
            glutPostRedisplay();
            break;
        case 'z':
            // Move forward (decrease z position)
            cameraZ -= 0.1f;
            glutPostRedisplay();
            break;
        case 'Z':
            // Move backward (increase z position)
            cameraZ += 0.1f;
            glutPostRedisplay();
            break;
        case 'y':
            cameraY -= 0.1f;
            glutPostRedisplay();
            break;
        case 'Y':
            cameraY += 0.1f;
            glutPostRedisplay();
            break;
    }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}