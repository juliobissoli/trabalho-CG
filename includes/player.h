#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "shot.h"
#include "polygon.h"
#include "collision.h"
#include "surface.h"

#include <iostream>
#include <tuple>



#define INITIAL_X 0.0
#define INITIAL_Y 0.0
#define INITIAL_ANGLE 0.0
// #define body_height 40.0
// #define body_width 25.0
// #define radius_header 20.0
// #define arm_width 30.0
// #define arm_height 5.0
// #define legs_width 10.0
// #define legs_height 30.0


#define MOVE_UNIT 1

using namespace std;


class Player {
    int _live;
    GLfloat gX;
    GLfloat gY;
    GLfloat gAngleArm;
    int gAngleLeg;
    GLfloat yCenter;
    GLfloat xCenter;
    Surface* _surface;
    Shot* _shot;
    Collision* _obstacle;
    Surface* _floor;
    bool  success_game;


    int gFacing; // Sentido para onde o personagem esta virado 0 para frente 1 para traz
    int junping;  // flag para informar se o personagem esta pulando
    GLfloat yInitJump; // posição inicial do pulo em y
    float timerJump;


    tuple <float, float, float> _body_color;
    tuple <float, float, float> _shot_color;

    float body_height;
    float body_width;
    float radius_header;
    float arm_width;
    float arm_height;
    float legs_width;
    float legs_height;

    float height_player;

    float move_init;

    
  
  private:
    void drawBody(GLint x, GLint y);
    void drawArm(GLint x, GLint y, GLint angle);
    void drawHeader(GLint x, GLint y);
    void drawLeg(GLint x, GLint y, int main_lag);
    void drawPlayer(GLint x, GLint y, GLint angle);
    void drawRef(GLint x, GLint y);
    void handleAjusteSize();


  public:
    Player(float x_init, float y_init,string color) {
        _live = 1;
        gX =  x_init;//250;
        gY =  y_init + ( arm_height  + body_height) / 2;
        gAngleArm = INITIAL_ANGLE + 2;
        gAngleLeg = 0;
        yCenter =  gY + (body_height / 2);
        xCenter =  (body_width / 2);
        gFacing = 1;
        junping = 0; //Inicializa com o personagem estatico
        yInitJump = gY;
        timerJump = -1;
        _floor = NULL;
        _shot = NULL;
        _surface = new Surface(gX, gY - (legs_height) , body_width, height_player);
        if(color == "green") _body_color = {0.0, 0.5, 0.0};
        else _body_color = {1.0, 0.0, 0.0};
        success_game = false;
    };


    void draw() {
        if(_live > 0){
          drawPlayer(gX, gY, gAngleArm);
        }
        else {
          cout << "++ TA MORTO ++\n";
        }
        // printf(" Bateu aqui ==> %f \n", gX);
    };

    void moveInX(GLfloat dx);
    void moveSurfaceInX(GLfloat dx);
    void moveArm(GLfloat dy);
    void moveArm2(GLfloat dy, GLfloat dx);
    void jump(GLdouble clock, Collision* collision);
    int hasJumping();
    void stopJump();
    void moveInY(GLfloat dy);
    void invertFacing(){gFacing = gFacing * -1;}
    int getFacing(){return gFacing;}
    tuple<GLfloat, GLfloat>getPos(){return make_tuple(gX, gY);}
    GLfloat getX(){return gX;};
    Shot* shootGun();
    void moveShot(float deltaTime, Collision* obstacles);
    void handleGravity(float deltaTime, Collision* obstacles);
    bool playerCollision(tuple<GLfloat, GLfloat> pointer);

    void decrementLive(){_live -= 1;}

    Surface* getSurface(){return _surface;}
    int live(){return _live;}
    Shot* getShot(){return _shot;}
    float getMoveUnit(){return move_init;}
    void reciseHeight(float dy){height_player = dy;}
    void setSuccesPlayer(bool value){this->success_game = value;}
    bool success(){return this->success_game;}
};


#endif /*PLAYER_H*/