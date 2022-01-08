#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

#include "world.h"
#include "polygon.h"

class World {

    GLfloat gX;
    GLfloat gY;

    private:
      void drawObstacles(GLint x, GLint y);

    public:
      World(){
          gX = 250;
          gY = 0; 
      }
     void build() {
         drawObstacles(gX, gY);
     };
};

#endif /*WORLD_H*/