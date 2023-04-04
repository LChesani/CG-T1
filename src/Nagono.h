#ifndef __NAGONO_H__
#define __NAGONO_H__

#include "gl_canvas2d.h"

struct cor{
    int r, g, b;
};

class Nagono{
    int x;
    int y;
    int z; //profundidade
    int r; //raio
    int n; //numero de lados
    float angulo;
    cor *borda;
    cor *preench;

public:
    Nagono(int _x, int _y, int _z, int _r, int _n, float angulo, cor *_borda, cor *_preench);
    void transform(int _x, int _y, int _r, float angulo, cor *_borda, cor *_preench);
    void render();
};

#endif