#ifndef __NAGONO_H__
#define __NAGONO_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "gl_canvas2d.h"
#include "gl_canvas2d.h"

struct cor{
    float r, g, b;
};

class Nagono{
    int x;
    int y;
    int z; //profundidade
    float r; //raio
    int n; //numero de lados
    float angulo;
    cor borda;
    cor preench;
public:
    Nagono(int _x, int _y, int _z, int _r, int _n, float angulo, cor _borda, cor _preench);
    Nagono();
    void transform(int _n, int _z, int _r, float ang, cor _borda, cor _preench);
    void render();
    int getZ() const;
    int colidiu(int mx, int my);
    void move(int _x, int _y);
    int getN();
    float getR();
    int getAng();
    char *getBorda();
    char *getPreench();
    float *getAngPointer();
    float *getRadiusPointer();

    float *getBordaR();
    float *getBordaG();
    float *getBordaB();
    int getX();
    int getY();
    float *getPreenchR();
    float *getPreenchG();
    float *getPreenchB();
};

#endif