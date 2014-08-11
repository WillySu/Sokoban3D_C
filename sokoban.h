#ifndef SOKOBAN_H_INCLUDED
#define SOKOBAN_H_INCLUDED

#include "commonWebGL.h"

#define BOX_ROW 6
#define BOX_COL 6
#define EMPTY_CODE 0
#define SOKOBAN_CODE 1
#define WODDEN_BOX_CODE 2
#define IRON_BOX_CODE 3

float BOX_LEN = 1,
    BOX_LINE_COLOR[3] = {0, 0, 0},
    BOX_WODDEN_LINE[3] = {0.65, 0.49, 0.24},
    BOX_WODDEN_COLOR[3] = {0.71, 0.65, 0.26},
    IRON_BOX_LINE[3] = {0.75, 0.75, 0.75},
    //BOX_IRON_COLOR[3] = {0.136, 0.136, 0.136};
    BOX_IRON_COLOR[3] = {0.27, 0.27, 0.27},
    GROUND_LINE_COLOR[3] = {0.4, 0.4, 0.4},
    GROUND_FILL_COLOR[3] = {0.5, 0.5, 0.5},
    SOKOBAN_COLOR[3] = {0, 0, 1};

int BOX_MAP[BOX_ROW][BOX_COL] = {
    {3, 3, 3, 3, 3, 3},
    {3, 0, 0, 0, 0, 3},
    {3, 0, 1, 2, 0, 0},
    {3, 0, 2, 0, 0, 0},
    {3, 0, 0, 0, 0, 3},
    {3, 3, 3, 3, 3, 3}
};

int sokobanRow, sokobanCol;

void drawWoddenBox () {
    drawBox(BOX_LEN, BOX_WODDEN_COLOR, BOX_WODDEN_LINE);
}

void drawIronBox () {
    drawBox(BOX_LEN, BOX_IRON_COLOR, IRON_BOX_LINE);
}

void drawSokoban () {
    glColor3f(SOKOBAN_COLOR[0], SOKOBAN_COLOR[1], SOKOBAN_COLOR[2]);
    glutSolidSphere(0.5, 32, 32);
}

void drawGround () {
    float halfW = BOX_COL/2-0.5,
        halfH = BOX_ROW/2-0.5,
        posY = -0.5,
        i, j;
    glBegin(GL_POLYGON);
    glColor3f(GROUND_FILL_COLOR[0], GROUND_FILL_COLOR[1], GROUND_FILL_COLOR[2]);
    glVertex3f(  halfW, posY, -halfH );
    glVertex3f(  halfW, posY,  halfH );
    glVertex3f( -halfW, posY,  halfH );
    glVertex3f( -halfW, posY, -halfH );
    glEnd();

    glLineWidth(3);
    //Vertical lines
    for (i=-halfW; i<halfW; i++) {
        float startP[3] = {i, posY, -halfH},
            endP[3] = {i, posY, halfH};
        drawLine(startP, endP, GROUND_LINE_COLOR);
    }
    //Horizontal lines
    for (j=-halfH; j<halfH; j++) {
        float startP[3] = {-halfW, -0.5, j},
            endP[3] = {halfH, -0.5, j};
        drawLine(startP, endP, GROUND_LINE_COLOR);
    }
}

void getSokobanBox (int boxCode, int row, int col) {
    switch (boxCode) {
        case SOKOBAN_CODE:
            //also update Sokoban's position here
            sokobanRow = row;
            sokobanCol = col;
            drawSokoban();
            break;
        case WODDEN_BOX_CODE:
            drawWoddenBox();
            break;
        case IRON_BOX_CODE:
            drawIronBox();
            break;
    }
}

void loopBoxMap () {
    int row, col, cur_val;

    drawGround();
    glTranslatef(-BOX_COL/2, 0, -BOX_ROW/2); //center the grid
    for (row=0; row<BOX_ROW; row++) {
        if (row>0) {
            glTranslatef(0, 0, 1);
            glTranslatef(-(BOX_COL-1), 0, 0); //reset COL to zero
        }
        for (col=0; col<BOX_COL; col++) {
            if (col>0) {
                glTranslatef(1, 0, 0);
            }
            cur_val = BOX_MAP[row][col];
            getSokobanBox(cur_val, row, col);
        }
    }
}

bool swapBoxVal (int curRow, int curCol, int newRow, int newCol) {
    int tmp = BOX_MAP[curRow][curCol];
    BOX_MAP[curRow][curCol] = BOX_MAP[newRow][newCol];
    BOX_MAP[newRow][newCol] = tmp;
}

bool canMove (int curRow, int curCol, int rowAdjust, int colAdjust, bool doRecursive) {
    int row = curRow + rowAdjust,
        col = curCol + colAdjust,
        val;
    if (row < 0 || row > BOX_ROW-1
        || col < 0 || col > BOX_COL-1) {
        return false; //outside of array limit
    } else {
        val = BOX_MAP[row][col];
        if (val == IRON_BOX_CODE || val == SOKOBAN_CODE) {
            return false; //cannot push Iron Box or Sokoban itself
        } else if (doRecursive && val == WODDEN_BOX_CODE) {
             //extra check when next to a wodden box, to make sure the space next to the wodden box is empty
            if (canMove(row, col, rowAdjust, colAdjust, false)) {
                swapBoxVal(curRow, curCol, row, col);
                return true;
            } else {
                return false;
            }
        } else if (val == EMPTY_CODE) { //can always move to an empty space
            swapBoxVal(curRow, curCol, row, col);
            return true;
        }
    }
    return false;
}

bool canMoveSokoban (int rowAdjust, int colAdjust, bool doRecursive) {
    canMove(sokobanRow, sokobanCol, rowAdjust, colAdjust, doRecursive);
}

bool canMoveLeft () {
    return canMoveSokoban(0, -1, true);
}

bool canMoveRight () {
    return canMoveSokoban(0, 1, true);
}

bool canMoveTop () {
    return canMoveSokoban(-1, 0, true);
}

bool canMoveBottom () {
    return canMoveSokoban(1, 0, true);
}

#endif // SOKOBAN_H_INCLUDED
