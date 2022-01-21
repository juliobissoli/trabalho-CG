#include "./includes/shot.h"
#include <cstdio>
#include <math.h>
#define DISTANCIA_MAX 500 * 3



void Shot::drawShot(GLfloat x, GLfloat y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    circle(radiusBullet,0,0,0);
    glPopMatrix();

}

void Shot::move(GLdouble deltaTime) {
    _x += gVel * cos(-gDirectionAng * M_PI / 180) * deltaTime * gDirection;
    _y += gVel * sin(gDirectionAng * M_PI / 180) * deltaTime  * gDirection;

    _surface->resetX(_x);
    _surface->resetY(_y);
}

Shot::~Shot() {}

bool Shot::valid() {

    // if(world->botCollision(_x, _y) != NULL){
    //     cout << "ACERTO UMA PLAYER \n";
    //     return false;
    // }

     return DISTANCIA_MAX > sqrt(pow(_x, 2) + pow(_y, 2));
}
