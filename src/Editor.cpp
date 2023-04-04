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
std::list <Nagono*> nagonos;
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

static void TextBoxRender(){
   for(TextBox *b : caixas){
      b->borda(0, 0, 0);
      b->render(1, 1, 1);
   }
}

static void NagonosRender(){
   for(Nagono *n : nagonos){
      n->render();
   }
}

static void TextBoxClick(int mx, int my){
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

static int getInfo(TextBox *b){
   int info = atoi(b->getText());
   b->cleanText();
   return info;
}

static cor *strToCor(char *str){
   cor *self = new cor();
   char aux[4];
   aux[0] = str[1];
   aux[1] = str[2];
   aux[2] = str[3];
   aux[3] = '\0';
   self->r = atoi(aux);
   aux[0] = str[5];
   aux[1] = str[6];
   aux[2] = str[7];
   self->g = atoi(aux);
   aux[0] = str[9];
   aux[1] = str[10];
   aux[2] = str[11];
   self->b = atoi(aux);
   return self;
}

static void genNagon(int mx, int my){
   if(gerar->Colidiu(mx, my)){
      auto it = caixas.begin();
      int n_lados = getInfo(*it); //informacao da primeira caixa
      ++it;
      int radius = getInfo(*it); //informacao da segunda caixa
      ++it;

      char *borda = (*it)->getText(); //informacoes de rgb da borda
      (*it)->cleanText();
      ++it;

      char *preench = (*it)->getText(); //informacoes de rgb do preenchimento
      (*it)->cleanText();
      ++it;

      int ang = getInfo(*it); //angulo de rotacao da figura
      ++it;

      int layer = getInfo(*it); // "z" da figura, determina a profundidade

      cor *corBorda = strToCor(borda);
      //printf("\ncor = %d, %d, %d", corBorda->r, corBorda->g, corBorda->b);
      cor *corPreench = strToCor(preench);
      nagonos.push_back(new Nagono(w/2, h/2, layer, radius, n_lados, ang, corBorda, corPreench));
   }
}

void loadEditor(int _w, int _h, int mx, int my, int click){
   
   CV::clear(1,1,1);
   NagonosRender();
   CV::color(1);
   CV::rectFill(0, _h*80/100, _w, _h);
   CV::color(0, 0, 0);
   CV::rect(0, _h*80/100, _w, _h);
   TextBoxRender();
   
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
      TextBoxClick(mx, my);
      genNagon(mx, my);
   }
}