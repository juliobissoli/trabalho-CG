#include "./includes/world.h"

#include <cstdio>
#include <math.h>
#define MOVE_UNIT 1

void World::drawObstacles(GLfloat x, GLfloat y)
{
  glPushMatrix();
  glTranslatef(x, y, 0);
  rectangle(size_bloc, size_bloc, 0, 0.2, 0);
  circle(3, 0.5, 0.5, 0.5);
  glPopMatrix();
}

void World::build(float _test[2][4]){
  //  drawObstacles(gX, gY);
  cout << "=======Build do mundo======= \n";
  for (int i = 0; i < 2; i++){
    Surface *s = new Surface(_test[i][0], _test[i][1], _test[i][2], _test[i][3]);
    _surfaces.push_back(s);
  }
};

void World::draw(){
  surface->draw();
  for (auto s : _surfaces) {
    s->draw();
  }
}

void World::desenhaRef(){
  glPushMatrix();
  glTranslatef(gX - 25, gY, 0);
  circle(3, 0.5, 0.5, 0.5);
  glPopMatrix();
}

void World::moveInX(GLfloat dx)
{
  int unit = MOVE_UNIT;
  gX += (dx * unit);
  surface->resetX(gX);
  for (auto s : _surfaces)
  {
    s->traslateX(dx * unit);
  }
}

// float World::getLeft(){
//     return gX - size_bloc/2;
// };

// World::~World() {}