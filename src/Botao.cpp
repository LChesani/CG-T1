#include "Botao.h"


Botao::Botao(float _x, float _y, float _larg, float _alt, char *_label){
     altura  = _alt;
     largura = _larg;
     x = _x;
     y = _y;
     strcpy(label, _label);
}


void Botao::render(int r, int g, int b){
    CV::color(0, 0, 0);
    CV::rect(x, y, x + largura, y + altura);
    CV::color(r, g, b);
    CV::rectFill(x, y, x + largura, y + altura);
    CV::color(0, 0, 0);
    CV::text(x+15, -2+y+altura/2, label); //escreve o label do botao mais ou menos ao centro.
  }