#include "TextBox.h"

TextBox::TextBox(float _x, float _y, float _larg, float _alt, char *_label){
     uso = 0;
     altura  = _alt;
     largura = _larg;
     x = _x;
     y = _y;
     strcpy(text, "");
     strcpy(label, _label);
}

void TextBox::setUso(int _uso){
    uso = _uso;
}
int TextBox::getUso(){
    return uso;
}


void TextBox::bs(){
    int i = 0;
    while(1){
        if(text[i+1] == '\0'){
        text[i] = '\0';
        return;
        }
        i++;
    }
}

char* TextBox::getText(){
    return text;
}

void TextBox::incText(char *_text){
    strcat(text, _text);
}

void TextBox::borda(int r, int g, int b){
    CV::color(r, g, b);
    CV::rect(x, y, x + largura, y + altura);
}

//recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao


void TextBox::render(int r, int g, int b)
{
    CV::color(r, g, b);
    CV::rectFill(x, y, x + largura, y + altura);
    CV::color(0, 0, 0);
    CV::text(x+10, y+altura/2, text); //escreve o text do botao mais ou menos ao centro.
    CV::text(x, y+50, label);
}
