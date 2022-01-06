#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "shot.h"
#include "polygon.h"


#define INITIAL_X 0
#define INITIAL_Y -80
#define INITIAL_ANGLE 0

#define body_height 80
#define body_width 45

#define radius_header 30
#define arm_width 50
#define arm_height 10
#define legs_width 10
#define legs_height 50


#define MOVE_UNIT 1


class Player {
    GLfloat gX;
    GLfloat gY;
    GLfloat gAngleArm;

  private:
    void drawBody(GLint x, GLint y);
    void drawArm(GLint x, GLint y, GLint angle);
    void drawHeader(GLint x, GLint y);
    void drawLegs(GLint x, GLint y);
    void drawPlayer(GLint x, GLint y, GLint angle);

  public:
    Player() {
        gX = INITIAL_X;
        gY = INITIAL_Y;
        gAngleArm = INITIAL_ANGLE;
    };
    void Desenha() {
        drawPlayer(gX, gY, gAngleArm);
        // printf(" Bateu aqui ==> %f \n", gX);
    };

    void moveInX(GLfloat dx);
    void moveArm(GLfloat dy);

    Shot* shootGun();
 
};


#endif /*PLAYER_H*/