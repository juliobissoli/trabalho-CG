#include "./includes/world.h"


#include <cstdio>
#include <math.h>


// void World::drawObstacles(GLfloat x, GLfloat y) {
//     glPushMatrix();
//     glTranslatef(x, y, 0);
//     rectangle(gX, gY ,0,0,0);
//     glPopMatrix();

// }

      void World::drawObstacles(GLint x, GLint y){
        glPushMatrix();
        glTranslatef(x, y, 0);
        rectangle(50, 50 ,0,0,0);
        glPopMatrix();
      }

// void World::move(GLdouble deltaTime) {
//     gX += gVel * cos(-gDirectionAng * M_PI / 180) * deltaTime * gDirection;
//     gY += gVel * sin(gDirectionAng * M_PI / 180) * deltaTime  * gDirection;
// }

// World::~World() {}