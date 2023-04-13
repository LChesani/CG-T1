#ifndef __EDITOR_H__
#define __EDITOR_H__
#include "gl_canvas2d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void resetOffset();
void clk(int v);
void loadEditor(int _w, int _h, int mx, int my, int state);
void editorOnKey(int key);
void initEditor(int _w, int _h);
void editorBackspace(void);
void TextBoxClick(int mx, int my);
void genNagon(int mx, int my);
void atualizaNagon(int mx, int my);
void salvar();
void recuperar();
void apagaFigura();
void onlyClick(int state, int mx, int my, int _h);
#endif