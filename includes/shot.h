#ifndef SHOT_H
#define SHOT_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

#include "polygon.h"
#include "surface.h"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <tuple>

using namespace std;

class Shot
{
  GLfloat _x_init;
  GLfloat _y_init;
  GLfloat _x;
  GLfloat _y;
  GLfloat gDirectionAng;
  GLfloat gVel;
  GLint gDirection;
  Surface *_surface;
  float radiusBullet;

private:
  void drawShot(GLfloat x, GLfloat y);

public:
  Shot(GLfloat x, GLfloat y, GLfloat directionAng, GLint direction, float r_bullet)
  {
    _x_init = x;
    _y_init = y;
    _x = x;
    _y = y;
    gDirectionAng = directionAng;
    gVel = 1 / r_bullet;
    gDirection = direction; // 1 para frente -1 para traz
    radiusBullet = r_bullet;
    _surface = new Surface(x, y, radiusBullet * 2, radiusBullet * 2);
  };
  ~Shot();
  void draw() { drawShot(_x, _y); };
  void move(GLdouble deltaTime);
  // bool valid();

  tuple<GLfloat, GLfloat> getPos()
  {
    tuple<GLfloat, GLfloat> pos = {_x, _y};
    return pos;
  };
  Surface *getSurface() { return _surface; }
};

#endif /* SHOT_H */
