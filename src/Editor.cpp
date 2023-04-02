#include "Editor.h"
#include "Botao.h"
#include <list>

#define NUM_BOTOES 6

int w, h;
int xl = 0;
int yl1 = 0;
int yl2 = 0;
int turn = 0;

std::list <Botao*> botoes;

void editorBackspace(void){
   for(Botao *b : botoes){
      char aux[2];
      if(b->getUso()){
         b->bs();
      }
   }
}

void editorOnKey(int key){
   for(Botao *b : botoes){
      char aux[2];
      if(b->getUso()){
         aux[0] = key;
         aux[1] = '\0';
         b->incLabel(aux);
      }
   }
}


void initEditor(int _w, int _h){
   for(int i = 0; i < NUM_BOTOES; i++){
      w = _w;
      h = _h;
      CV::color(1, 1, 1);
      CV::rectFill(0, h*80/100, w, h);
      CV::color(0);
      CV::rect(0, h*80/100, w, h);
      int wb = w*15/100;
      int hb = h*5/100;
      int inix = i*wb + w*NUM_BOTOES/100;
      int iniy = h*88/100;
      botoes.push_back(new Botao(inix, iniy, wb-w*5/100, hb, ""));
   }
}

void loadEditor(int _w, int _h, int mx, int my, int click){
   
   CV::clear(1,1,1);
   CV::color(1);
   CV::rectFill(0, _h*80/100, _w, _h);
   for(Botao *b : botoes){
      b->borda(0, 0, 0);
      b->Render(1, 1, 1, mx, my);
   }

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
   for(Botao *b : botoes){
      if(b->getUso()){
         aux = strlen(b->getLabel())*10 + 10;
      }
   }
   CV::line(xl+aux, yl1, xl+aux, yl2);
   
   if(click){
      
      for(Botao *b : botoes){
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

