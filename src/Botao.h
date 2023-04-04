#ifndef __BOTAO_H__
#define __BOTAO_H__


#include "gl_canvas2d.h"
#include "Controlador.h"

class Botao : public Controlador{
  char label[50];
public:
  Botao(float _x, float _y, float _larg, float _alt, char *_label);
  

  void render(int r, int g, int b);

};

#endif
