#ifndef __BOTAO_H__
#define __BOTAO_H__


#include "gl_canvas2d.h"

class Botao{
  float altura, largura, x, y;
  char label[100];
  int uso;
public:
  Botao(float _x, float _y, float _larg, float _alt, char *_label)
  {
     uso = 0;
     altura  = _alt;
     largura = _larg;
     x = _x;
     y = _y;
     strcpy(label, _label);
  }
  void setUso(int _uso){
    uso = _uso;
  }
  int getUso(){
    return uso;
  }
  int getAltura(){
    return altura;
  }
  int getLargura(){
    return largura;
  }
  int getX(){
    return x;
  }
  int getY(){
    return y;
  }

  void bs(){
    int i = 0;
    while(1){
      if(label[i+1] == '\0'){
        label[i] = '\0';
        return;
      }
      i++;
    }
  }

  void setLabel(char *_label){
    strcpy(label, _label);
  }

  char *getLabel(){
    return label;
  }

  void incLabel(char *text){
    strcat(label, text);
  }
    
  void borda(int r, int g, int b){
    CV::color(r, g, b);
    CV::rect(x, y, x + largura, y + altura);
  }

  //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
  bool Colidiu(int mx, int my)
  {
      if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura) )
      {
          return true;
      }
      return false;
  }

  void Render(int r, int g, int b, int mouseX, int mouseY)
  {
      CV::color(r, g, b);
      CV::rectFill(x, y, x + largura, y + altura);
      CV::color(0, 0, 0);
      CV::text(x+10, y+altura/2, label); //escreve o label do botao mais ou menos ao centro.
  }

  

};

#endif
