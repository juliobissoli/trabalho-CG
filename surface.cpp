#include "includes/surface.h"

void Surface::drowSurface(){

    // printf("Ta batendo auqui _x %f, _y %f _ySize %f _xSize %f\n", _x, _y, _ySize, _xSize);
    glPushMatrix();
    glTranslatef(_x, _y, 0);
    rectangle(_ySize, _xSize, get<0>(_color), get<1>(_color), get<2>(_color));
    glPopMatrix();
}

void Surface::desenhaRef(int position){
    glPushMatrix();
    if(position == -1)glTranslatef(_x, _y, 0.0);            //onde esta x e y da superficie
    if(position == 0) glTranslatef(getLeft(), getTop() - (_ySize /2), 0.0);     //ponto da esquerda
    if(position == 1) glTranslatef(_x, getTop(), 0.0);      //ponto de cima
    if(position == 2) glTranslatef(getRight(),getTop() - ( _ySize /2), 0.0);    //ponto da direita
    if(position == 4) glTranslatef(_x, getBooton(), 0.0);   //ponto da baixo
    circle(1, 0.5, 0.5, 0.5);
    glPopMatrix();
}


bool Surface::isInternal(GLfloat x, GLfloat y){

   return x <= getRight() && x >= getLeft() && y <= getTop() && y >= getBooton();
}
