#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

#include "world.h"
#include "polygon.h"
#include "surface.h"

#define size_bloc 50.0

class World {

    GLfloat gX;
    GLfloat gY;
    Surface *surface;

    private:
      void drawObstacles(GLint x, GLint y);
      void desenhaRef();

    public:
      World(){
          gX = 50;
          gY = 0; 
          surface =  new Surface( gX, gY, size_bloc, size_bloc);
      }
     void build() {
        //  drawObstacles(gX, gY);
        surface->draw();
     };

    Surface* getSurface(){return surface;}


    void moveInX(GLfloat dx);
    float getTop(){return gY + (size_bloc / 2);}
    float getLeft(){return gX - (size_bloc / 2);}


};

#endif /*WORLD_H*/