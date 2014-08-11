// Author: Willy Su
// Created: August 9, 2014
// Project: Sokoban 3D
// Reference: Matt Daisley's mycube.c (4/25/2012)

#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "sokoban.h"

// Global Variables
int rotateX, rotateY, orthoVal;

void resetValues () {
    rotateX = 60;
    rotateY = -25;
    orthoVal = 6;
}

void printInstruction () {
    //printf("Rotate X: %i\n", rotateX);
    //printf("Rotate Y: %i\n", rotateY);
    //printf("Zoom: %i\n", orthoVal);
    printf("// Author: Willy Su\n\
// Created: August 9, 2014\n\
// Project: Sokoban 3D\n\
// Reference: Matt Daisley's mycube.c (4/25/2012)\n\
//\n\
// Controls:\n\
// Left Arrow   - Move Sokoban to Left\n\
// Right Arrow  - Move Sokonab to Right\n\
// Up Arrow     - Move Sokonab to Up\n\
// Down Arrow   - Move Sokonab to Down\n\
// r            - Reset\n\
// z            - Zoom In\n\
// x            - Zoom Out\n\
// a            - Camera Rotate Left\n\
// d            - Camera Rotate Right\n\
// w            - Camera Rotate Up\n\
// s            - Camera Rotate Down");
}

void display () {
    //Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //Zoom in and out
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-orthoVal, orthoVal, -orthoVal, orthoVal, -orthoVal*2, orthoVal*2);

    //Camera angle
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0, 0, -1, 0, 0, 0, 0, 1, 0);
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
    //gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
    //gluLookAt(0, 0, 0, 0, 0, -1, 0, 2, 0);

    // Rotate when user changes rotateX and rotateY
    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);

    //Draw Axis X, Y and Z
    drawAxis();

    loopBoxMap();

    glFlush();
    glutSwapBuffers();
}

void specialKeys ( int key, int x, int y ) {
    bool returnVal = false;
    if (key == GLUT_KEY_RIGHT) {
        returnVal = canMoveRight();
    } else if (key == GLUT_KEY_LEFT) {
        returnVal = canMoveLeft();
    } else if (key == GLUT_KEY_UP) {
        returnVal = canMoveTop();
    } else if (key == GLUT_KEY_DOWN) {
        returnVal = canMoveBottom();
    }
    if (returnVal) {
        glutPostRedisplay();
    }

}

void normalKeys ( unsigned char key, int x, int y ) {
    if (key == 'd') {
        rotateY += 5;
    } else if (key == 'a') {
        rotateY -= 5;
    } else if (key == 'w') {
        rotateX += 5;
    } else if (key == 's') {
        rotateX -= 5;
    } else if (key == 'x') {
        orthoVal += 1;
    } else if (key == 'z') {
        orthoVal -= 1;
    } else if (key == 'r') {
        resetValues();
    }
    glutPostRedisplay();
}

// main() function
int main ( int argc, char* argv[] ) {
    printInstruction();
    resetValues();
    // Initialize GLUT and process user parameters
    glutInit(&argc, argv);
    // Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Create window
    glutInitWindowSize(640, 640);
    glutCreateWindow("Sokoban 3D");
    // Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    // Callback functions
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(normalKeys);

    glutMainLoop();

    return 0;
}
