#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Nagono.h"
#include "gl_canvas2d.h"

Nagono::Nagono(int _x, int _y, int _r, int _n){
    x = _x;
    y = _y;
    r = _r;
    n = _n;
}

void Nagono::transform(int _x, int _y, int _r){
    x = _x;
    y = _y; 
    r = _r;
}

void Nagono::render(cor borda, cor preench){
    CV::color(borda.r, borda.g, borda.b);
    CV::circle(x, y, r, n);
    CV::color(preench.r, preench.g, preench.b);
    CV::circleFill(x, y, r, n);
}