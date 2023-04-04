#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__


#include "gl_canvas2d.h"
#include "Controlador.h"

class TextBox : public Controlador{
  char text[100];
  char label[50];
  int uso;
public:
  TextBox(float _x, float _y, float _larg, float _alt, char *_label);
  void setUso(int _uso);
  int getUso();

  void bs();
  
  char *getText();

  void incText(char *_text);
    
  void borda(int r, int g, int b);

  void cleanText();
  //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
  

  void render(int r, int g, int b);

};

#endif
