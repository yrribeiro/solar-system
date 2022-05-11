#include<iostream>
#include<GL/gl.h>
#include<GL/glut.h>
#include<GL/glu.h>

#define WIDTH 850
#define HEIGHT 600
#define X 1100
#define Y 10

typedef struct TRI_DIM_COORDINATES {
    float x, y, z;
}TRI_DIM_COORDINATES;

static GLfloat orbitAngleInnerPlanet = 50.0f;
static GLfloat orbitAngleOuterPlanet = 360.0f;
static GLfloat orbitAngleMoonY = 0.0f;
static GLfloat orbitAngleMoonX = 45.0f;
static TRI_DIM_COORDINATES coordinates;
static TRI_DIM_COORDINATES moonY;
static TRI_DIM_COORDINATES moonX;

void displaySolarSystem();
void drawSun();
void drawInnerPlanet();
void drawOuterPlanet();
void drawMoonX();
void drawMoonY();
void handleKeyboardStroke(unsigned char key, int x, int y);

int main(int argc, char** argv){
    const char *TITLE = "Solar System Prototype";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow(TITLE);
    glutPositionWindow(X, Y);
    glutDisplayFunc(displaySolarSystem);
    glutKeyboardFunc(handleKeyboardStroke);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float FOV_Y = 45.0f;
    gluPerspective(FOV_Y, 1.0f*WIDTH/HEIGHT, 0.1f, 1050.0f);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

void displaySolarSystem(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLdouble CAMERA_POS_X = 0.0f, CAMERA_POS_Y = 0.0f, CAMERA_POS_Z = 5.0f;
    gluLookAt(
        CAMERA_POS_X,
        CAMERA_POS_Y,
        CAMERA_POS_Z,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f
    );
    drawSun();
    drawInnerPlanet();
    drawOuterPlanet();
    glutSwapBuffers();
}

void drawSun(){
    glTranslatef(0.0f, 0.0f, -300.0f);
    glColor3ub(255, 198, 26);
    glutSolidSphere(20.0f, 30, 30);
}

void drawInnerPlanet(){
    glPushMatrix();

    glRotatef(orbitAngleInnerPlanet, coordinates.x, coordinates.y, coordinates.z);
    glTranslatef(90.0f, 0.0f, 0.0f);
    glColor3ub(130, 72, 0);
    glutSolidSphere(4.0f, 15, 15);

    glPopMatrix();
}

void drawOuterPlanet(){
    glRotatef(orbitAngleOuterPlanet, coordinates.x, coordinates.y, coordinates.z);
    glTranslatef(-90.0f, 0.0f, 0.0f);
    glColor3ub(51, 85, 255);
    glutSolidSphere(9.0f, 15.5f, 15.5f);

    drawMoonY();
    drawMoonX();
}

void drawMoonY(){
    glPushMatrix();
	glRotatef(orbitAngleMoonY, moonY.x, moonY.y, moonY.z);
	glTranslatef(20.0f, 0.0f, 1.0f);
    glColor3ub(192, 192, 192);
	glutSolidSphere(2, 200, 200);
    glPopMatrix();
}

void drawMoonX(){
    glPushMatrix();
	glRotatef(orbitAngleMoonX, moonX.x, moonX.y, moonX.z);
	glTranslatef(10.0f, 0.0f, 0.0f);
    glColor3ub(192, 192, 192);
	glutSolidSphere(1, 200, 200);
    glPopMatrix();
}

void handleKeyboardStroke(unsigned char key, int x, int y){
    key = tolower(key);
    if (key == 'y'){
        coordinates.x = 0.0f;
        coordinates.y = 1.0f;
        coordinates.z = 0.0f;
        orbitAngleInnerPlanet += 1.0f;         // move INNER planet
        if (orbitAngleInnerPlanet > 360.0f) orbitAngleInnerPlanet = 0.0f;


        orbitAngleOuterPlanet -= 1.0f;        // move OUTER planet
        if (orbitAngleOuterPlanet == 0) orbitAngleOuterPlanet = 360.0f;

        moonY.x = 0;
        moonY.y = 1;
        moonY.z = 0;
        orbitAngleMoonY += 5.0f;               // move moon in Y-AXIS
        if (orbitAngleMoonY > 360.0f) orbitAngleMoonY = 0.0f;

        moonX.x = 0;
        moonX.y = 1;
        moonX.z = 1;
        orbitAngleMoonX +=5.0f;               // move moon in X-AXIS
        if (orbitAngleMoonX > 360.0f) orbitAngleMoonX = 0.0f;

    }

    glutPostRedisplay();
}