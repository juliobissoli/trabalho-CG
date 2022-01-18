#ifndef SHOT_H
#define SHOT_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>


#include "polygon.h"
#include <stdio.h>
#define radiusBullet 5

class Shot {
    GLfloat gx_init;
    GLfloat gy_init;
    GLfloat gX;
    GLfloat gY;
    GLfloat gDirectionAng;
    GLfloat gVel;
    GLint gDirection;

  private:
    void drawShot(GLfloat x, GLfloat y);

  public:
    Shot(GLfloat x, GLfloat y, GLfloat directionAng, GLint direction) {
        gx_init = x;
        gy_init = y;
        gX = x;
        gY = y;
        gDirectionAng = directionAng;
        gVel = 2;
        gDirection = direction; // 1 para frente -1 para traz
    };
    ~Shot();
    void draw() { drawShot(gX, gY); };
    void move(GLdouble deltaTime);
    bool valid();
    void getPos(GLfloat& xOut, GLfloat& yOut) {
        xOut = gX;
        yOut = gY;
    };
    void getVel(GLfloat& velOut) { velOut = gVel; };
    void getDirectionAng(GLfloat& directionAngOut) {
        directionAngOut = gDirectionAng;
    };
};

#endif /* SHOT_H */
