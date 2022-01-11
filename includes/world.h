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
    Surface *surface;
    vector<vector<float>> matrix(float, vector<float>);
    // std::vector<std::vector<float> > matrix(2, std::vector<float>(4));
    vector<Surface*> _surfaces;
    

    private:
      void drawObstacles(GLint x, GLint y);
      void desenhaRef();

      GLfloat _test = {{gX, gY, size_bloc, size_bloc}, {gX*2, gY*2, size_bloc, size_bloc}};


    public:
      World(){
          gX = 250;
          gY = 0; 
          surface =  new Surface( gX, gY, size_bloc, size_bloc);
          std::set<vector<float>> matrix = {{gX, gY, size_bloc, size_bloc}, {gX*2, gY*2, size_bloc, size_bloc}};
      }
     void build() {
        //  drawObstacles(gX, gY);
        for(int i = 0; i < 2; i++ ){
          Surface *s =  new Surface( _test[1][0], _test[1][1], _test[1][2], _test[1][3]);
          s->draw();

        }
        surface->draw();
     };

    Surface* getSurface(){return surface;}


    void moveInX(GLfloat dx);
    float getTop(){return gY + (size_bloc / 2);}
    float getLeft(){return gX - (size_bloc / 2);}


};

#endif /*WORLD_H*/