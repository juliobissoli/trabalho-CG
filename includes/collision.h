#ifndef COLLISION_H
#define COLLISION_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

#include "surface.h"

#include <iostream>
#include <vector>
#include <set>
#include <tuple>

#define MAX_VIEW_X 700
#define MAX_VIEW_Y 400

using namespace std;

class Collision
{

  GLfloat _max_x;
  GLfloat _max_y;

  Surface *_objStatics[MAX_VIEW_X][MAX_VIEW_Y];
  void setSurfaceInMat(Surface *s);
  Surface *_floor;
  Surface *_roof;
  GLfloat _x_ref;

private:
  Surface *handleAvaliatePointer(Surface *s, string x_direction, string y_direction);
  tuple<int, int> handleeGetPointer(Surface *s, string x_direction, string y_direction);

public:
  Collision(int width, int height)
  {
    _x_ref = 0;
    _max_x = width;
    _max_y = height;
    _floor = new Surface(0, 0, MAX_VIEW_X, 0);
  }

  // Monta o array de superficies (obstáculos);
  void build(vector<Surface *> surfaces);
  void printMat();
  Surface *detectCollision(Surface *s, string direction);
  bool inpactPointer(tuple<GLfloat, GLfloat> point);
  void resetXRef(GLfloat dx) { _x_ref = dx; }
  Surface *hasFloor(Surface *s);
  bool finishWord(Surface *s);
  bool finishWordPlayer(float facing, float x_gab_start);
};

bool collisionS2S(Surface *s1, Surface *s2);

#endif /*COLLISION_H*/