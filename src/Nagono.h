#ifndef __NAGONO_H__
#define __NAGONO_H__

#include "gl_canvas2d.h"

struct cor{
    int r, g, b;
};

class Nagono{
    int x;
    int y;
    int r; //raio
    int n; //numero de lados

public:
    Nagono(int _x, int _y, int _r, int _n);
    void transform(int _x, int _y, int _r);
    void render(cor borda, cor preench);
};

#endif