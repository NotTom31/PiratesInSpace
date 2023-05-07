#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include<stdio.h>

float cameraX = 0.0f;
float cameraY = 6.0f;
float cameraZ = 12.0f;

GLuint ship;
char ch='1';

void loadObj(char *fname)
{
FILE *fp;
int read;
GLfloat x, y, z;
char ch;
ship=glGenLists(1);
fp=fopen(fname,"r");
if (!fp) 
    {
        printf("can't open file %s\n", fname);
	  exit(1);
    }
glPointSize(2.0);
glNewList(ship, GL_COMPILE);
{
glPushMatrix();
glBegin(GL_POINTS);
while(!(feof(fp)))
 {
  read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
  if(read==4&&ch=='v')
  {
   glVertex3f(x,y,z);
  }
 }
glEnd();
}
glPopMatrix();
glEndList();
fclose(fp);
}

//.obj loader code ends here

void init(void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glEnableClientState (GL_VERTEX_ARRAY);
    glEnableClientState (GL_COLOR_ARRAY);
    glEnable(GL_DEPTH_TEST);
}

GLfloat groundVertices[][3] = {
    {0.0, 0.0, -15.0},   // Vertex 1
    {-15.0, 0.0, 0.0},   // Vertex 2
    {0.0, 0.0, 15.0},   // Vertex 3
    {15.0, 0.0, 0.0}    // Vertex 4
};

GLfloat islandTop[][3]={
    {0.0 ,-3.0, 0.0},
    {-1.68, -1.65, 0.0},
    {-0.9, 0.0, 0.0},
    {0.9, 0.0, 0.0},
    {1.68, -1.65, 0.0}
};

GLfloat islandBottom[][3]={
    {0.0, -3.0, 0.5},
    {-1.68, -1.65, 0.5},
    {-0.9, 0.0, 0.5},
    {0.9, 0.0, 0.5},
    {1.68, -1.65, 0.5}
};

GLfloat islandSideOne[][3]={
    {0.0 ,-3.0, 0.0},
    {-1.68, -1.65, 0.0},
    {-1.68, -1.65, 0.5},
    {0.0, -3.0, 0.5}
};

GLfloat islandSideTwo[][3]={
    {-1.68, -1.65, 0.0},
    {-0.9, 0.0, 0.0},
    {-0.9, 0.0, 0.5},
    {-1.68, -1.65, 0.5}
};
GLfloat islandSideThree[][3]={
    {-0.9, 0.0, 0.0},
    {0.9, 0.0, 0.0},
    {0.9, 0.0, 0.5},
    {-0.9, 0.0, 0.5}
};
GLfloat islandSideFour[][3]={
    {0.9, 0.0, 0.0},
    {1.68, -1.65, 0.0},
    {1.68, -1.65, 0.5},
    {0.9, 0.0, 0.5}
};

GLfloat islandSideFive[][3] = {
    {1.68, -1.65, 0.0},
    {0.0 ,-3.0, 0.0},
    {-0.9, 0.0, 0.0},
    {1.68, -1.65, 0.5}
};
//for tree
GLfloat treeTop[][3]={
    {0.0, 3.0, 0.0},
    {0.0, 3.0, 0.5},
    {0.5, 3.0, 0.5},
    {0.5, 3.0, 0.0}
};

GLfloat treeBottom[][3]={
    {0.0,0.0,0.0},
    {0.0,0.0,0.5},
    {0.5,0.0,0.5},
    {0.5,0.0,0.0}
};

GLfloat treeSideOne[][3]{
    {0.0, 3.0, 0.0},
    {0.0, 3.0, 0.5},
    {0.0, 0.0, 0.5},
    {0.0, 0.0, 0.0}
};

GLfloat treeSideTwo[][3]{
    {0.0, 3.0, 0.5},
    {0.5, 3.0, 0.5},
    {0.5, 0.0, 0.5},
    {0.0, 0.0, 0.5}
};

GLfloat treeSideThree[][4]{
    {0.5, 3.0, 0.5},
    {0.5, 3.0, 0.0},
    {0.5, 0.0, 0.0},
    {0.5, 0.0, 0.5}
};

GLfloat treeSideFour[][5]{
    {0.5, 3.0, 0.0},
    {0.0, 3.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.5, 0.0, 0.0}
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
void drawTree(){
    glColor3f(0.71f, 0.53f, 0.39f); // light brown color
    glBegin(GL_QUADS);
    glVertex3fv(treeTop[0]);
    glVertex3fv(treeTop[1]);
    glVertex3fv(treeTop[2]);
    glVertex3fv(treeTop[3]);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3fv(treeBottom[0]);
    glVertex3fv(treeBottom[1]);
    glVertex3fv(treeBottom[2]);
    glVertex3fv(treeBottom[3]);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3fv(treeSideOne[0]);
    glVertex3fv(treeSideOne[1]);
    glVertex3fv(treeSideOne[2]);
    glVertex3fv(treeSideOne[3]);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3fv(treeSideTwo[0]);
    glVertex3fv(treeSideTwo[1]);
    glVertex3fv(treeSideTwo[2]);
    glVertex3fv(treeSideTwo[3]);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3fv(treeSideThree[0]);
    glVertex3fv(treeSideThree[1]);
    glVertex3fv(treeSideThree[2]);
    glVertex3fv(treeSideThree[3]);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3fv(treeSideFour[0]);
    glVertex3fv(treeSideFour[1]);
    glVertex3fv(treeSideFour[2]);
    glVertex3fv(treeSideFour[3]);
    glEnd();
}

void drawPyramid()
{
    // Define the vertices of the pyramid
    GLfloat vertices[][3] = {
        {0.0, 1.0, 0.0},    // Vertex 0 (top)
        {-1.0, -1.0, 1.0},  // Vertex 1 (front left)
        {1.0, -1.0, 1.0},   // Vertex 2 (front right)
        {1.0, -1.0, -1.0},  // Vertex 3 (back right)
        {-1.0, -1.0, -1.0}  // Vertex 4 (back left)
    };

    // Set the color of the pyramid
    glColor3f(0.0, 1.0, 0.0);

    // Draw the pyramid
    glBegin(GL_TRIANGLES);

    // Front face
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[2]);

    // Right face
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[3]);

    // Back face
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[4]);

    // Left face
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[1]);

    // Bottom face
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[4]);

    glEnd();
}

void drawBoat()
{
    glPushMatrix();
 	glTranslatef(0,-40.00,-105);
    glScalef(0.1,0.1,0.1);
    glCallList(ship);
 	glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();             /* clear the matrix */
    /* viewing transformation  */
    gluLookAt (cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
        drawGround();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-5.0f, 0.5f, 0.0f);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    drawIsland();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, 0.5f, -1.0f);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.8f, 3.0f, -1.0f);
    drawPyramid();
    glPopMatrix();

    drawBoat();

    glFlush();
}


void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
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
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   loadObj("Ship/Ship.obj");
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}