#include "Editor.h"
#include "TextBox.h"
#include "Botao.h"
#include "Nagono.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#define NUM_textBox 6
#define HUD _h*70/100

int w, h;
int xl = 0;
int yl1 = 0;
int yl2 = 0;
int turn = 0;
int clicking = 0;
int offX = 0;
int offY = 0;

std::list <TextBox*> caixas;
std::list <Nagono*> nagonos;
std::list <Botao*> botoes;

Nagono *selecionado = (Nagono*) malloc(sizeof(Nagono));
TextBox *uso = (TextBox*) malloc(sizeof(TextBox));


static void carregaPropriedades(){
   auto it =  caixas.begin();
   (*it)->setText(selecionado->getN());
   ++it;
   (*it)->setText(selecionado->getR());
   ++it;
   (*it)->setText(selecionado->getBorda());
   ++it;
   (*it)->setText(selecionado->getPreench());
   ++it;
   (*it)->setText(selecionado->getAng());
   ++it;
   (*it)->setText(selecionado->getZ()); 
}

void clk(int v){
   clicking = v;
}

void resetOffset(){
   offX = 0;
   offY = 0;
}

void createSlider(float x, float y, float width, float height, float minValue, float maxValue, float *value, int mx, int my, int cor) {
    // Definimos um valor de sensibilidade para a borda do slider
    float sensitivity = 0.001;
    
    // Desenha o slider
    CV::color(cor);
    CV::rectFill(x, y, x + width, y + height);
    
    // Calcula a posição do botão no slider
    float buttonX = x + ((*value - minValue) / (maxValue - minValue)) * width;
    float buttonY = y + (height / 2);
    
    // Desenha o botão
    CV::color(1, 1, 1);
    CV::circleFill(buttonX, buttonY, height / 2, 10, 0);
    
    // Verifica se o mouse está sobre o botão
    if(clicking && my >= y && my <= y + height ){
      carregaPropriedades();
      if (mx >= buttonX - height / 2 && mx <= buttonX + height / 2) {
         // Calcula a nova posição do botão baseado na posição do mouse
         buttonX = mx;
         buttonX = std::max(buttonX, x + height / 2);
         buttonX = std::min(buttonX, x + width - height / 2);
         
         // Calcula o novo valor baseado na posição do botão
         *value = minValue + ((buttonX - x - height / 2) / (width - height)) * (maxValue - minValue);
      } 
      else if (mx >= x && mx <= x + width) {
         // Verifica se o mouse está próximo às bordas do slider
         if (mx <= x + height / 2) {
               // Se estiver próximo à borda do valor mínimo, ajustamos o valor do controlador para o mínimo do slider
               *value = minValue;
         } else if (mx >= x + width - height / 2) {
               // Se estiver próximo à borda do valor máximo, ajustamos o valor do controlador para o máximo do slider
               *value = maxValue;
         } else {
               // Caso contrário, calculamos o novo valor baseado na posição do mouse e levando em conta a sensibilidade da borda
               float offset = ((mx - x - height / 2) / (width - height)) * (maxValue - minValue);
               if (offset < 0) {
                  offset *= (1 - sensitivity);
               } else {
                  offset *= (1 + sensitivity);
               }
               *value = minValue + offset;
         }
      }
    }
}






void apagaFigura(){
   nagonos.remove(selecionado);
   selecionado = nullptr;
}








void editorBackspace(void){
   if(uso != nullptr)
      uso->bs();
}


void salvar(){
   std::ofstream arquivo("imagem.dog", std::ios::out | std::ios::binary);
   for (auto it = nagonos.begin(); it != nagonos.end(); ++it) {
      arquivo.write(reinterpret_cast<const char*>(*it), sizeof(Nagono));
   }
}

void recuperar(){
   std::ifstream arquivo("imagem.dog", std::ios::in | std::ios::binary);
   Nagono *nagon = new Nagono();
   while (arquivo.read(reinterpret_cast<char*>(nagon), sizeof(Nagono))) {
      nagonos.push_back(nagon);
      nagon = new Nagono();
   }
}

void editorOnKey(int key){
   if(uso != nullptr){
      char *aux = (char*) malloc(2 * sizeof(char));
      aux[0] = key;
      aux[1] = '\0';
      uso->incText(aux);
   }
}


void initEditor(int _w, int _h){
   selecionado = nullptr;
   uso = nullptr;
   const char *labels[] = {"Num de lados", "Escala", "Borda", "Preenchimento", "Angulo", "Camada"};
   for(int i = 0; i < NUM_textBox; i++){
      w = _w;
      h = _h;
      CV::color(1, 1, 1);
      CV::rectFill(0, h*70/100, w, h);
      CV::color(0);
      CV::rect(0, h*70/100, w, h);
      int wb = w*15/100;
      int hb = h*5/100;
      int inix = i*wb + w*NUM_textBox/100;
      int iniy = h*88/100;
      caixas.push_back(new TextBox(inix, iniy, wb-w*5/100, hb, labels[i]));
   }
   botoes.push_back(new Botao(_w * 90/100, _h*75/100, 80, 50, (char*)("Gerar"))); //forcei a conversao para parar de dar warnings
   botoes.push_back(new Botao(_w * 80/100, _h*75/100, 115, 50, (char*)("Atualizar")));
}

static void TextBoxRender(){
   for(TextBox *b : caixas){
      b->borda(0, 0, 0);
      b->render(1, 1, 1);
   }
}

static bool sortByLayer(const Nagono *a, const Nagono *b) {
   return a->getZ() < b->getZ();
}


static bool sortByFront(const Nagono *a, const Nagono *b) {
   return a->getZ() > b->getZ();
}

static void NagonosRender(){
   nagonos.sort(sortByLayer); //ele vai plotar primeiro os q tem layer menor
   for(Nagono *n : nagonos){
      n->render();
   }
}

void TextBoxClick(int mx, int my){
   for(TextBox *b : caixas){
      if(b->Colidiu(mx, my)){
         xl = b->getX();
         yl1 = b->getY()+b->getAltura()/10;
         yl2 = b->getY()+b->getAltura()-b->getAltura()/10;
         uso = b;
         return;
      }
   }
   uso = nullptr;
}

static int getInfo(TextBox *b){
   int info = atoi(b->getText()); //string para inteiro
   b->cleanText();
   return info;
}

static cor *strToCor(char *str){
   cor *self = (cor*) malloc(sizeof(cor));
   char aux[4];
   aux[0] = str[0];
   aux[1] = str[1];
   aux[2] = str[2];
   aux[3] = '\0';
   self->r = std::stof(aux)/255;

   aux[0] = str[4];
   aux[1] = str[5];
   aux[2] = str[6];
   self->g = std::stof(aux)/255;

   aux[0] = str[8];
   aux[1] = str[9];
   aux[2] = str[10];
   self->b = std::stof(aux)/255;

   return self;
}

void genNagon(int mx, int my){
   if(botoes.front()->Colidiu(mx, my)){
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

      nagonos.push_back(new Nagono(w/2, h/2, layer, radius, n_lados, ang, *strToCor(borda), *strToCor(preench)));
   }
}

void atualizaNagon(int mx, int my){
   if(botoes.back()->Colidiu(mx, my) && selecionado != nullptr){
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

      selecionado->transform(n_lados, layer, radius, ang, *strToCor(borda), *strToCor(preench));
   }
}

static void cursor(int xl, int yl1, int yl2){
   if(uso != nullptr){
      int aux = 0;
      aux = strlen(uso->getText())*10+10;
      CV::line(xl+aux, yl1, xl+aux, yl2);
   }
}

static void interface(int _w, int _h){
   CV::color(1);
   CV::rectFill(0, HUD, _w, _h);
   CV::color(0, 0, 0);
   CV::rect(0, HUD, _w, _h);
}

static void countCursor(){
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
}


void calculaOffset(int mx, int my){
   offX = mx-selecionado->getX();
   offY = my-selecionado->getY();
}


static void selection(int mx, int my, int _h){
   nagonos.sort(sortByFront);
   for(Nagono *n : nagonos){
      if(n->colidiu(mx, my)){
         selecionado = n;
         calculaOffset(mx, my);
         carregaPropriedades();
         return;
      }
   }
   if(my > HUD){ //pra ele n desmarcar o bagulho caso clique no hud
      return;
   }
   selecionado = nullptr;
}

static void loadSliders(int _h, int mx, int my){
   createSlider(275,_h*83/100,115, 20, 0, 400, selecionado->getRadiusPointer(), mx, my, 14);

   createSlider(465,_h*83/100,115, 20, 0, 1, selecionado->getBordaR(), mx, my, 2);
   createSlider(465,_h*78/100,115, 20, 0, 1, selecionado->getBordaG(), mx, my, 3);
   createSlider(465,_h*73/100,115, 20, 0, 1, selecionado->getBordaB(), mx, my, 4);

   createSlider(660,_h*83/100,115, 20, 0, 1, selecionado->getPreenchR(), mx, my, 2);
   createSlider(660,_h*78/100,115, 20, 0, 1, selecionado->getPreenchG(), mx, my, 3);
   createSlider(660,_h*73/100,115, 20, 0, 1, selecionado->getPreenchB(), mx, my, 4);

   createSlider(850,_h*83/100,115, 20, 0, 360, selecionado->getAngPointer(), mx, my, 14);
}

static void selecionadoMarca(){
   CV::color(1, 1, 0);
   for(int i = 0; i < 5; i++)
      CV::circle(selecionado->getX(), selecionado->getY(), selecionado->getR()+i+10, 200, 45);
}





static void arrasta(int _w, int _h, int mx, int my){
   if(selecionado != nullptr && clicking && !botoes.front()->Colidiu(mx, my) && !botoes.back()->Colidiu(mx, my) && my < HUD){ //garantir que nao vai clicar em um botao e arrastar o tareco
      selecionado->move(mx-offX, my-offY);
   }
}

void onlyClick(int state, int mx, int my, int _h){
   if(selecionado != nullptr){
      calculaOffset(mx, my);
   }
   selection(mx, my, _h);
}



void loadEditor(int _w, int _h, int mx, int my, int state){
   NagonosRender();
   interface(_w, _h);
   TextBoxRender();
   botoes.front()->render(0, 1, 0);
   botoes.back()->render(1, 1, 0);
   countCursor();
   cursor(xl, yl1, yl2); //desenha a barrinha das caixas de texto
   arrasta(_w, _h, mx, my);
   if(selecionado != nullptr){
      selecionadoMarca();
      loadSliders(_h, mx, my);
   }
}