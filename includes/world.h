#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

#include "world.h"
#include "polygon.h"
#include "surface.h"

#define size_bloc 50.0

#include <iostream>
#include <vector>
#include <set>

  
using namespace std;

class World {

    GLfloat gX;
    GLfloat gY;
    Surface *surface; //remover isso apos resolver colizões
    // vector<vector<float>> matrix(float, vector<float>);
    // std::vector<std::vector<float> > matrix (float(2), std::vector<float>(4));
    vector<Surface*> _surfaces;
    

    private:
      void drawObstacles(GLfloat x, GLfloat y);
      void desenhaRef();

    public:
      World(){
          gX = 50;
          gY = 0; 
          surface =  new Surface( gX, gY, size_bloc, size_bloc);

      }

      // Monta o array de superficies (obstáculos); 
     void build(float _test[2][4]);

     void draw();

    Surface* getSurface(){return surface;}


    void moveInX(GLfloat dx);
    float getTop(){return gY + (size_bloc / 2);}
    float getLeft(){return gX - (size_bloc / 2);}


};

#endif /*WORLD_H*/