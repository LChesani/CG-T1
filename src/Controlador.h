#ifndef __CONTROLADOR_H__
#define __CONTROLADOR_H__


class Controlador{
public:
    int altura, largura, x, y;
    bool Colidiu(int mx, int my);
    int getAltura();
    int getLargura();
    int getX();
    int getY();
};



#endif