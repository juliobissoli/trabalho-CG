#include "./includes/world.h"


#include <cstdio>
#include <math.h>
#define MOVE_UNIT 1



void World::drawObstacles(GLint x, GLint y){
  glPushMatrix();
  glTranslatef(x, y, 0);
  rectangle(size_bloc, size_bloc ,0, 0.2,0);
  circle(3, 0.5, 0.5, 0.5);
  glPopMatrix();
}

void World::desenhaRef(){
    glPushMatrix();
  glTranslatef(gX - 25, gY, 0);
  circle(3, 0.5, 0.5, 0.5);
  glPopMatrix();
}


void World::moveInX(GLfloat dx){
    int unit = MOVE_UNIT;
    gX += (dx * unit);
    surface->resetX(gX);
    printf("Move world x =>\t %f \n", gX);
}

    // float World::getLeft(){
    //     return gX - size_bloc/2;
    // };



// World::~World() {}