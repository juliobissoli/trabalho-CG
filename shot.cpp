#include "./includes/shot.h"
#include <cstdio>
#include <math.h>
#define DISTANCIA_MAX 500



void Shot::drawShot(GLfloat x, GLfloat y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    circle(radiusBullet,0,0,0);
    glPopMatrix();

}

void Shot::move(GLdouble deltaTime) {
    gX += gVel * cos(-gDirectionAng * M_PI / 180) * deltaTime;
    gY += gVel * sin(gDirectionAng * M_PI / 180) * deltaTime ;
}

Shot::~Shot() {}

bool Shot::valid() { return DISTANCIA_MAX > sqrt(pow(gX, 2) + pow(gY, 2)); }
