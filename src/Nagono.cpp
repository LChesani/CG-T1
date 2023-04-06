#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Nagono.h"
#include "gl_canvas2d.h"

Nagono::Nagono(int _x, int _y, int _z, int _r, int _n, float ang, cor *_borda, cor *_preench){
    borda = _borda;
    preench = _preench;
    angulo = ang;
    x = _x;
    y = _y;
    z = _z;
    r = _r;
    n = _n;
}


void Nagono::transform(int _x, int _y, int _r, float ang, cor *_borda, cor *_preench){
    borda = _borda;
    preench = _preench;
    angulo = ang;
    x = _x;
    y = _y; 
    r = _r;
}

int Nagono::getZ() const{
    return z;
}

void Nagono::render(){
    CV::color(borda->r, borda->g, borda->b);
    CV::circle(x, y, r, n, angulo);
    CV::color(preench->r, preench->g, preench->b);
    CV::circleFill(x, y, r, n, angulo);
}
