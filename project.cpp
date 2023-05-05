#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

float cameraX = 0.0f;
float cameraY = 3.0f;
float cameraZ = 8.0f;

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

GLfloat islandTop[][3]={
    {0.0 ,-1.0, 0.0},
    {-0.56, -0.55, 0.0},
    {-0.3, 0.0, 0.0},
    {0.3, 0.0, 0.0},
    {0.56, -0.55, 0.0}
};

GLfloat islandBottom[][3]={
    {0.0, -1.0, 0.5},
    {-0.56, -0.55, 0.5},
    {-0.3, 0.0, 0.5},
    {0.3, 0.0, 0.5},
    {0.56, -0.55, 0.5}
};

GLfloat islandSideOne[][3]={
    {0.0 ,-1.0, 0.0},
    {-0.56, -0.55, 0.0},
    {-0.56, -0.55, 0.5},
    {0.0, -1.0, 0.5}
};

GLfloat islandSideTwo[][3]={
    {-0.56, -0.55, 0.0},
    {-0.3, 0.0, 0.0},
    {-0.3, 0.0, 0.5},
    {-0.56, -0.55, 0.5}
};
GLfloat islandSideThree[][3]={
    {-0.3, 0.0, 0.0},
    {0.3, 0.0, 0.0},
    {0.3, 0.0, 0.5},
    {-0.3, 0.0, 0.5}
};
GLfloat islandSideFour[][3]={
    {0.3, 0.0, 0.0},
    {0.56, -0.55, 0.0},
    {0.56, -0.55, 0.5},
    {0.3, 0.0, 0.5}
};

GLfloat islandSideFive[][3] = {
    {0.56, -0.55, 0.0},
    {0.0 ,-1.0, 0.0},
    {-0.3, 0.0, 0.0},
    {0.56, -0.55, 0.5}
};

void drawGround(){
    //Ground Plane
    glColor3f(0.0, 0.8, 1.0);
    // Draw the rectangle
    glBegin(GL_QUADS);
        glVertex3fv(groundVertices[0]);
        glVertex3fv(groundVertices[1]);
        glVertex3fv(groundVertices[2]);
        glVertex3fv(groundVertices[3]);
    glEnd();
}

void drawIsland(){

    glColor3f(194/255.0, 178/255.0, 128/255.0);
    glBegin(GL_POLYGON); // start defining a polygon
        for(int i = 0; i < 5; i++) {
            glVertex3fv(islandTop[i]); // add each vertex to the polygon
        }
    glEnd(); // end defining the polygon
    glBegin(GL_POLYGON); // start defining a polygon
        for(int i = 0; i < 5; i++) {
            glVertex3fv(islandBottom[i]); // add each vertex to the polygon
        }
    glEnd(); // end defining the polygon
    glBegin(GL_QUADS);
        glVertex3fv(islandSideOne[0]);
        glVertex3fv(islandSideOne[1]);
        glVertex3fv(islandSideOne[2]);
        glVertex3fv(islandSideOne[3]);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3fv(islandSideTwo[0]);
        glVertex3fv(islandSideTwo[1]);
        glVertex3fv(islandSideTwo[2]);
        glVertex3fv(islandSideTwo[3]);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3fv(islandSideThree[0]);
        glVertex3fv(islandSideThree[1]);
        glVertex3fv(islandSideThree[2]);
        glVertex3fv(islandSideThree[3]);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3fv(islandSideFour[0]);
        glVertex3fv(islandSideFour[1]);
        glVertex3fv(islandSideFour[2]);
        glVertex3fv(islandSideFour[3]);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3fv(islandSideFive[0]);
        glVertex3fv(islandSideFive[1]);
        glVertex3fv(islandSideFive[2]);
        glVertex3fv(islandSideFive[3]);
    glEnd();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity ();             /* clear the matrix */
    /* viewing transformation  */
    gluLookAt (cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
        drawGround();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0f, 0.5f, 0.0f);
    glRotatef( 90.0, 1.0, 0.0, 0.0);
    drawIsland();
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