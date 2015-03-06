#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

/*Function Prototypes */
void sierpinskiTriangleWrapper(GWindow &canvas);
void drawSierpinskiTriangle(double x, double y, double length, int order, GWindow &canvas);
void drawTriangle(double x, double y, double sidelength, GWindow &canvas);
/* Main program */

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 500;
const double M_PI = 3.14;

/*
 * Major help from br1992
 * Page: https://github.com/br1992
 */
int main() {
   GWindow gw(WINDOW_WIDTH, WINDOW_HEIGHT);
   sierpinskiTriangleWrapper(gw);


   return 0;
}

void sierpinskiTriangleWrapper(GWindow &canvas) {
    while(true) {
        int length = getInteger("Enter edge length: ");
        int order = getInteger("Enter fractal order: ");
        canvas.clear();
        double height = sin(M_PI * .6666) * length;
        drawSierpinskiTriangle(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - height/2, length, order, canvas);
    }
}

void drawSierpinskiTriangle(double x, double y, double length, int order, GWindow &canvas) {
    //Final order, draw triangle
    if(order == 0) {
        drawTriangle(x, y, length, canvas);
        return;
    }
    double height = sin(M_PI * .6666) * length;
    drawSierpinskiTriangle(x - length/4, y + height/2, length/2, order - 1, canvas); // bottom left triangle
    drawSierpinskiTriangle(x + length/4, y + height/2, length/2, order - 1, canvas); // bottom right
    drawSierpinskiTriangle(x,y, length/2, order - 1, canvas); //top middle triangle
}

void drawTriangle(double x, double y, double sidelength, GWindow &canvas) {
    double trigHeight = sin(M_PI * .6666) * sidelength;
    canvas.drawLine(x, y, x + sidelength/2, y + trigHeight); //draw right line
    canvas.drawLine(x, y, x - sidelength/2, y + trigHeight); //draw left line
    canvas.drawLine(x - sidelength/2, y + trigHeight, x + sidelength/2, y + trigHeight); // draw bottom line
}
