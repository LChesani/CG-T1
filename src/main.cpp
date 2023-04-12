#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "Editor.h"
#include "TextBox.h"


//variavel global para selecao do que sera exibido na canvas.
int screenWidth = 1280, screenHeight = 720; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
int _state = 0;
int clicking = 0;
void DesenhaSenoide()
{
   float x=0, y;
   CV::color(1);
   CV::translate(20, 200); //desenha o objeto a partir da coordenada (200, 200)
   for(float i=0; i < 68; i+=0.001)
   {
      y = sin(i)*50;
      CV::point(x, y);
      x+=0.01;
   }
   CV::translate(0, 0);
}



//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.




void render()
{
   loadEditor(screenWidth, screenHeight, mouseX, mouseY, _state, clicking);
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   if(key == 19){
      salvar();
   }
   else if(key == 15){
      recuperar();
   }
   if(key == 8){
      editorBackspace();
   }

   else if(key == 127){
      apagaFigura();
   }

   else if(key < 200){
      editorOnKey(key);
   }

}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   //printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;
   _state = state;
   if(_state == 1){
      clicking = 0;
   }
   if(!_state){ //clicou
      clicking = 1;
      TextBoxClick(mouseX, mouseY);
      genNagon(mouseX, mouseY);
      atualizaNagon(mouseX, mouseY);
   }
}



int main(void){
   CV::init(&screenWidth, &screenHeight, "Cachorro");
   initEditor(screenWidth, screenHeight);
   CV::run();
}