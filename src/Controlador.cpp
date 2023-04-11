#include "Controlador.h"

int Controlador::getAltura(){
    return altura;
}

int Controlador::getLargura(){
    return largura;
}
int Controlador::getX(){
    return x;
}
int Controlador::getY(){
    return y;
}

bool Controlador::Colidiu(int mx, int my){
    
    if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura) ){
        return true;
    }
    return false;
}