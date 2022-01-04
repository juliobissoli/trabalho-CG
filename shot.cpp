#include "./shot.h"
#include <cstdio>
#include <math.h>
#define DISTANCIA_MAX 500

void Shot::drownCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 20) {
        glVertex2f(radius * cos(i * M_PI / 180), radius * sin(i * M_PI / 180));
    }
    glEnd();
}

void Shot::drownShot(GLfloat x, GLfloat y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    drownCirc(radiusBullet, 0, 0, 0);
    glPopMatrix();
}

void Shot::move(GLdouble deltaTime) {
    gX += gVel * sin(-gDirectionAng * M_PI / 180) * deltaTime;
    gY += gVel * cos(-gDirectionAng * M_PI / 180) * deltaTime;
}

Shot::~Shot() {}

bool Shot::valid() { return DISTANCIA_MAX > sqrt(pow(gX, 2) + pow(gY, 2)); }
