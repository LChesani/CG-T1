#include "Editor.h"
#include "TextBox.h"
#include "Botao.h"
#include "Nagono.h"
#include <list>

#define NUM_textBox 6

int w, h;
int xl = 0;
int yl1 = 0;
int yl2 = 0;
int turn = 0;

std::list <TextBox*> caixas;
Botao *gerar;

void editorBackspace(void){
   for(TextBox *b : caixas){
      char aux[2];
      if(b->getUso()){
         b->bs();
      }
   }
}

void editorOnKey(int key){
   for(TextBox *b : caixas){
      char aux[2];
      if(b->getUso()){
         aux[0] = key;
         aux[1] = '\0';
         b->incText(aux);
      }
   }
}


void initEditor(int _w, int _h){
   char *labels[] = {"Num de lados", "Escala", "Borda", "Preenchimento", "Angulo", "Camada"};
   for(int i = 0; i < NUM_textBox; i++){
      w = _w;
      h = _h;
      CV::color(1, 1, 1);
      CV::rectFill(0, h*80/100, w, h);
      CV::color(0);
      CV::rect(0, h*80/100, w, h);
      int wb = w*15/100;
      int hb = h*5/100;
      int inix = i*wb + w*NUM_textBox/100;
      int iniy = h*88/100;
      caixas.push_back(new TextBox(inix, iniy, wb-w*5/100, hb, labels[i]));
   }
   gerar = new Botao(_w * 90/100, _h*3/100, 80, 50, "Gerar");
}

void loadEditor(int _w, int _h, int mx, int my, int click){
   
   CV::clear(1,1,1);
   CV::color(1);
   CV::rectFill(0, _h*80/100, _w, _h);
   CV::color(0, 0, 0);
   CV::rect(0, _h*80/100, _w, _h);
   for(TextBox *b : caixas){
      b->borda(0, 0, 0);
      b->render(1, 1, 1);
   }
   gerar->render(0, 1, 0);
   if(turn < 300){
      CV::color(0, 0, 0);
   }
   else{
      CV::color(1, 1, 1);
      if(turn >= 600){
         turn = 0;
      } 
   }
   turn++;

   int aux = 0;
   for(TextBox *b : caixas){
      if(b->getUso()){
         aux = strlen(b->getText())*10 + 10;
      }
   }
   CV::line(xl+aux, yl1, xl+aux, yl2);
   
   if(click){
      for(TextBox *b : caixas){
         if(b->getUso()){
            b->setUso(0);
         }
         if(b->Colidiu(mx, my)){
            xl = b->getX();
            yl1 = b->getY()+b->getAltura()/10;
            yl2 = b->getY()+b->getAltura()-b->getAltura()/10;
            b->setUso(1);
         }
      }
   }



}