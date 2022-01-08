#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "shot.h"
#include "polygon.h"


#define INITIAL_X 0.0
#define INITIAL_Y 0.0
#define INITIAL_ANGLE 0.0
#define body_height 40.0
#define body_width 25.0
#define radius_header 20.0
#define arm_width 30.0
#define arm_height 5.0
#define legs_width 10.0
#define legs_height 30.0


#define MOVE_UNIT 1


class Player {
    GLfloat gX;
    GLfloat gY;
    GLfloat gAngleArm;
    GLfloat yCenter;
    GLfloat xCenter;
    int gFacing; // Sentido para onde o personagem esta virado 0 para frente 1 para traz

    int junping;  // flag para informar se o personagem esta pulando
    GLfloat yInitJump; // posição inicial do pulo em y
    float timerJump;
  
  private:
    void drawBody(GLint x, GLint y);
    void drawArm(GLint x, GLint y, GLint angle);
    void drawHeader(GLint x, GLint y);
    void drawLegs(GLint x, GLint y);
    void drawPlayer(GLint x, GLint y, GLint angle);

    void drawRef(GLint x, GLint y);

  public:
    Player() {
        gX = body_width + arm_width + 10;
        gY =   ( arm_height  + body_height) / 2;
        gAngleArm = INITIAL_ANGLE;
        yCenter =  gY + (body_height / 2);
        xCenter =  (body_width / 2);
        gFacing = 1;
        junping = 0; //Inicializa com o personagem estatico
        yInitJump = gY;
        timerJump = -1;
    };
    void Desenha() {
        drawPlayer(gX, gY, gAngleArm);
        // printf(" Bateu aqui ==> %f \n", gX);
    };

    void moveInX(GLfloat dx);
    void moveArm(GLfloat dy);
    void moveArm2(GLfloat dy, GLfloat dx);
    void jump(GLdouble clock);
    int hasJumping();

    Shot* shootGun();
 
};


#endif /*PLAYER_H*/