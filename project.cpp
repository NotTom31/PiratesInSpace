#include <GL/glut.h>
#include <stdlib.h>
#include<GL/gl.h>
#include <cmath>
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <string>
#include <stdio.h>
#include<fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ALCdevice* device;
ALCcontext* context;
ALuint buffer, source;

const char* MODEL_PATH = "Ship.obj";

float cameraX = 0.0f;
float cameraY = 6.0f;
float cameraZ = 16.0f;

GLuint ship;
char ch='1';

void init(void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glEnableClientState (GL_VERTEX_ARRAY);
    glEnableClientState (GL_COLOR_ARRAY);
    glEnable(GL_DEPTH_TEST);

    device = alcOpenDevice(nullptr);
    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

    // Load sound file
    FILE* fp = fopen("sound.wav", "rb");
    if (!fp) {
        std::cerr << "Failed to open sound file\n";
        exit(1);
    }

    // Read sound data
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* data = new char[size];
    fread(data, 1, size, fp);
    fclose(fp);

    // Create buffer and fill with sound data
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, data, size, 88200);

    // Create source and attach buffer
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_GAIN, 1.0f);
    alSourcef(source, AL_PITCH, 1.0f);

    // Play sound
    alSourcePlay(source);

    delete[] data;
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
 	glTranslatef(0,5,0);
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
    glScalef(1.5, 0.0, 1.5);
        drawGround();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-10.0f, 0.5f, 0.0f);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(3.0, 3.0, 3.0);
    drawIsland();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(10.0f, 0.5f, 4.0f);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    drawIsland();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(7.0f, 0.5f, -10.0f);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(0.7, 0.7, 0.7);
    drawIsland();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-7.0f, 0.5f, 10.0f);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(0.7, 0.7, 0.7);
    drawIsland();
    glPopMatrix();


//right island trees
    glPushMatrix();
    glTranslatef(10.0f, 0.5f, 4.0f);
    glScalef(0.5, 0.5, 0.5);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0f, 0.5f, 2.0f);
    glScalef(0.5, 0.5, 0.5);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.2f, 2.0f, 4.0f);
    glScalef(0.5,0.5,0.5);
    drawPyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.2f, 2.0f, 2.0f);
    glScalef(0.5,0.5,0.5);
    drawPyramid();
    glPopMatrix();

//left island trees
    glPushMatrix();
    glTranslatef(-10.0f, 0.5f, -1.0f);
    glScalef(0.5, 0.5, 0.5);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.0f, 0.5f, -1.5f);
    glScalef(0.5,0.5,0.5);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.0f, 0.5f, -2.0f);
    glScalef(0.5, 0.5, 0.5);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.0f, 0.5f, -3.0f);
    glScalef(0.5, 0.5, 0.5);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.8f, 2.0f, -1.0f);
    glScalef(0.5,0.5,0.5);
    drawPyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.8f, 2.0f, -1.5f);
    glScalef(0.5,0.5,0.5);
    drawPyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.8f, 2.0f, -2.0f);
    glScalef(0.5,0.5,0.5);
    drawPyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.8f, 2.0f, -3.0f);
    glScalef(0.5,0.5,0.5);
    drawPyramid();
    glPopMatrix();


    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(MODEL_PATH, aiProcess_Triangulate | aiProcess_FlipUVs);

    glScalef(0.05, 0.05, 0.05);
    glColor3f(0.5f, 0.35f, 0.05f);
    glTranslatef(0.0f, 50.0f, 0.0f);

    if (!scene) {
        std::cerr << "Failed to load model: " << importer.GetErrorString() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Render the meshes
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];

        glBegin(GL_TRIANGLES);
        for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; k++) {
                unsigned int index = face.mIndices[k];
                aiVector3D pos = mesh->mVertices[index];
                aiVector3D normal = mesh->mNormals[index];
                aiVector3D texcoord = mesh->mTextureCoords[0][index];
                glNormal3f(normal.x, normal.y, normal.z);
                glTexCoord2f(texcoord.x, texcoord.y);
                glVertex3f(pos.x, pos.y, pos.z);
            }
        }
        glEnd();
    }

    importer.FreeScene();
    glutSwapBuffers();
    glFlush();

}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27: // Escape key
            exit(0);
            break;
        case 'x':
            // Move left (decrease x position)
            cameraX -= 0.5f;
            glutPostRedisplay();
            break;
        case 'X':
            // Move right (increase x position)
            cameraX += 0.5f;
            glutPostRedisplay();
            break;
        case 'z':
            // Move forward (decrease z position)
            cameraZ -= 0.5f;
            glutPostRedisplay();
            break;
        case 'Z':
            // Move backward (increase z position)
            cameraZ += 0.5f;
            glutPostRedisplay();
            break;
        case 'y':
            cameraY -= 0.5f;
            glutPostRedisplay();
            break;
        case 'Y':
            cameraY += 0.5f;
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
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();

   // Clean up resources
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcDestroyContext(context);
    alcCloseDevice(device);
   return 0;
}