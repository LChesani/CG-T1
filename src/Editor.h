#ifndef __EDITOR_H__
#define __EDITOR_H__
#include "gl_canvas2d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void loadEditor(int _w, int _h);
void editorOnKey(int key);
void initEditor(int _w, int _h);
void editorBackspace(void);
void TextBoxClick(int mx, int my);
void genNagon(int mx, int my);
#endif
