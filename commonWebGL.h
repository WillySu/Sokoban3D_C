#ifndef COMMONWEBGL_H_INCLUDED
#define COMMONWEBGL_H_INCLUDED

#include <GL/glut.h>

void drawBox (float len, float fillColor[] , float lineColor[]) {
    glColor3f(fillColor[0], fillColor[1], fillColor[2]);
    glutSolidCube(len);
    glColor3f(lineColor[0], lineColor[1], lineColor[2]);
    glLineWidth(len*2);
    glutWireCube(len);
}

void drawLine (float startPoint[], float endPoint[], float lineColor[]) {
    glColor3f(lineColor[0], lineColor[1], lineColor[2]);
    glBegin(GL_LINES);
    glVertex3f(startPoint[0], startPoint[1], startPoint[2]);
    glVertex3f(endPoint[0], endPoint[1], endPoint[2]);
    glEnd();
}

void drawAxisX () {
    float startPoint[3] = {-100, 0, 0},
        endPoint[3] = {100, 0, 0},
        lineColor[3] = {1, 0, 0};
    drawLine(startPoint, endPoint, lineColor);
}

void drawAxisY () {
    float startPoint[3] = {0, -100, 0},
        endPoint[3] = {0, 100, 0},
        lineColor[3] = {0, 1, 0};
    drawLine(startPoint, endPoint, lineColor);
}

void drawAxisZ () {
    float startPoint[3] = {0, 0, -100},
        endPoint[3] = {0, 0, 100},
        lineColor[3] = {0, 0, 1};
    drawLine(startPoint, endPoint, lineColor);
}

void drawAxis () {
    glLineWidth(1);
    drawAxisX();
    drawAxisY();
    drawAxisZ();
}

#endif // COMMONWEBGL_H_INCLUDED
