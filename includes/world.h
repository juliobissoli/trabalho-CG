#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

#include "world.h"
#include "polygon.h"
#include "surface.h"
#include "player.h"


#include <iostream>
#include <vector>
#include <set>
#include<tuple>

#define size_bloc 50.0 //remover tamanho so para teste
#define MAX_VIEW_X 1500
#define MAX_VIEW_Y 500
  
using namespace std;

class World {

    GLfloat gX;
    GLfloat gY;
    // Surface *surface; //remover isso apos resolver colizões
    // vector<vector<float>> matrix(float, vector<float>);
    // std::vector<std::vector<float> > matrix (float(2), std::vector<float>(4));
    vector<Surface*> _surfaces;
    Player* oponente;
    

    private:
      void drawCircle(GLfloat x, GLfloat y);
      void desenhaRef();
      void setSurfaceInMat(Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y], Surface *s);

      tuple<int, int> handleeGetPointer(Surface* s, string x_direction, string y_direction  );
    public:
      World(){
          gX = 0;
          gY = 0; 
          oponente = new Player(300.0, 0.0, "red");
          // surface =  new Surface( gX, gY, size_bloc, size_bloc);

      }

      // Monta o array de superficies (obstáculos); 
    void build(float _test[2][4], Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y]);
    void draw();
    // Surface* getSurface(){return surface;}
    vector<Surface*> getSurfaces(){return _surfaces;};
    void moveInX(GLfloat dx);
    
    // Prarte de colisões vai sair
    // void printMat(Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y]);
    // Surface* detectCollision(Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y], Surface* s, string direction);
    
    // float getTop(){return gY + (size_bloc / 2);}
    // float getLeft(){return gX - (size_bloc / 2);}


};

#endif /*WORLD_H*/