#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "shot.h"


#define INITIAL_X 0
#define INITIAL_Y -100
#define body_height 80
#define body_width 60

#define MOVE_UNIT 1


class Player {
    GLfloat gX;
    GLfloat gY;

  private:
    void drownBody(GLint height, GLint width);
    void drownPlayer(GLint x, GLint y);

  public:
    Player() {
        gX = INITIAL_X;
        gY = INITIAL_Y;
    };
    void Desenha() {
        drownPlayer(gX, gY);
        // printf(" Bateu aqui ==> %f \n", gX);
    };

    void moveInX(GLfloat dx);

    Shot* shootGun();
 
};


#endif /*PLAYER_H*/