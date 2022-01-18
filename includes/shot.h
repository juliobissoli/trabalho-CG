#ifndef SHOT_H
#define SHOT_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>


#include "polygon.h"
// #include "world.h"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <tuple>

#define radiusBullet 5

using namespace std;


class Shot {
    GLfloat _x_init;
    GLfloat _y_init;
    GLfloat _x;
    GLfloat _y;
    GLfloat gDirectionAng;
    GLfloat gVel;
    GLint gDirection;

  private:
    void drawShot(GLfloat x, GLfloat y);

  public:
    Shot(GLfloat x, GLfloat y, GLfloat directionAng, GLint direction) {
        _x_init = x;
        _y_init = y;
        _x = x;
        _y = y;
        gDirectionAng = directionAng;
        gVel = 1;
        gDirection = direction; // 1 para frente -1 para traz
    };
    ~Shot();
    void draw() { drawShot(_x, _y); };
    void move(GLdouble deltaTime);
    bool valid();

    tuple<GLfloat, GLfloat> getPos(){
       tuple<GLfloat, GLfloat> pos = {_x, _y};
       return pos;
    };

    void getVel(GLfloat& velOut) { velOut = gVel; };
    void getDirectionAng(GLfloat& directionAngOut) {
        directionAngOut = gDirectionAng;
    };
};

#endif /* SHOT_H */
