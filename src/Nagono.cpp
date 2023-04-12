
#include "Nagono.h"


Nagono::Nagono(int _x, int _y, int _z, int _r, int _n, float ang, cor _borda, cor _preench){
    borda = _borda;
    preench = _preench;
    angulo = ang;
    x = _x;
    y = _y;
    z = _z;
    r = _r;
    n = _n;
}

Nagono::Nagono(){

};

float Nagono::getR(){
    return r;
}


static char* corToStr(cor c) {
    char* chars = (char*) malloc(12*sizeof(char));
    int _r = round(c.r*255);
    int _g = round(c.g*255);
    int _b = round(c.b*255);
    sprintf(chars, "%03d,%03d,%03d", _r, _g, _b); //converte as cores para o formato "RRR,GGG,BBB"
    return chars;
}

char *Nagono::getBorda(){
    return corToStr(borda);
}

char *Nagono::getPreench(){
    return corToStr(preench);
}

int Nagono::getN(){
    return n;
}

void Nagono::move(int _x, int _y){
    x = _x;
    y = _y;
}

void Nagono::transform(int _n, int _z, int _r, float ang, cor _borda, cor _preench){
    borda = _borda;
    preench = _preench;
    angulo = ang;
    n = _n;
    z = _z;
    r = _r;
}

int Nagono::getZ() const{
    return z;
}

int Nagono::getAng(){
    return angulo;
}

int Nagono::colidiu(int mx, int my){
    if(sqrt(pow(x-mx,2)+pow(y-my, 2)) <= r+10){ //considerando a porta de 10
        return 1;
    }
    return 0;
}

float *Nagono::getRadiusPointer(){
    return &r;
}

float *Nagono::getAngPointer(){
    return &angulo;
}

void Nagono::render(){
    CV::color(borda.r, borda.g, borda.b);
    for(int i = 0; i < 10; i++) //pra fazer uma borda mais gorducha
        CV::circle(x, y, r+i, n, angulo);
    CV::color(preench.r, preench.g, preench.b);
    CV::circleFill(x, y, r, n, angulo);
}