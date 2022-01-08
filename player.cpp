#include "./includes/player.h"
#include <string>
#include <cmath>

void Player::drawBody(GLint x, GLint y){
    glPushMatrix();
    glTranslatef(x, y, 0);
    rectangle(body_height, body_width, 0.0, 1.0, 0.0);
    glPopMatrix();
}


void Player::drawHeader(GLint x, GLint y){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glTranslatef(0,  (body_height + radius_header), 0);
    circle(radius_header, 0.0, 1.0, 0.0);
    glPopMatrix();
}

void Player::drawArm(GLint x, GLint y, GLint angle){
    glPushMatrix();
    
    glTranslatef(x,  0 , 0);
    glTranslatef(0 , y + (body_height /2), 0);
    glRotatef(angle, 0, 0, 1);
    glRotatef(90 + (90 * -gFacing), 0, 1, 0);

    glTranslatef(body_width / 2.0, 0,0);

    rectangle(arm_height, arm_width, 0.0, 0.0, 1.0);

    glPopMatrix();
}

void Player::drawLegs(GLint x, GLint y){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glTranslatef(0,  (-body_height + (body_height - legs_height)), 0);
    rectangle(legs_height, legs_width, 1.0, 0, 0);
    glPopMatrix();
}

void Player::drawRef(GLint x, GLint y){
        glPushMatrix();
        glTranslatef(x, y, 0);
        circle(10, 0.5, 0.5, 0.5);
        glPopMatrix();
}

void Player::drawPlayer(GLint x, GLint y, GLint angle){
    
    glPushMatrix();
    Player::drawBody(x, y);
    Player::drawArm(x,y, angle);
    Player::drawHeader(x,y);
    Player::drawLegs(x,y);
    glPopMatrix();

}

void Player::moveInX(GLfloat dx){
    int unit = MOVE_UNIT;
    gX += (dx * unit);
}

void Player::moveArm(GLfloat dy){
    int unit = MOVE_UNIT;
    if((gAngleArm < 45 && dy > 0) || (gAngleArm > -45 && dy < 0)){
        gAngleArm += (dy * unit);
    }
}



Shot *Player::shootGun(){
    
    //Calcular onde esta a ponta da arma para indicar de onde o diro sairá
    //Multiplicando pela direção (gFacing) para corigir o sentindo  p onde o personagem esta aponado
    double positionX = gX + (gFacing * arm_width * cos(gAngleArm * M_PI / 180));
    double positionY = gY + (body_height /2) + arm_height / 2 +  (gFacing * arm_width * sin(gAngleArm * M_PI / 180));
    
    return new Shot(positionX, positionY, gAngleArm, gFacing);
}

void Player::moveArm2(GLfloat dy, GLfloat dx){

    
    if(dx < gX)gFacing  = -1;
    else gFacing  = 1;
    // printf("gX= %f \t dX %f \t gFacing %d\n", gX, dx, gFacing);
    float y =  dy - yCenter;
    float x =  dx - xCenter;


    float theta = atan (y/x) * 180 / M_PI;
    if(theta < 45  && theta > -45 ){
        gAngleArm = theta * gFacing;
    }
}

void Player::jump(GLdouble clock){
    
    float dy = -(timerJump * timerJump) + 2*timerJump ;
    timerJump += (1 / clock );

    float max_jupm = (body_height + arm_height + legs_height) * 2;

    junping = 1;
    // gY = (dy *  gY ) + yInitJump;
    gY = -(timerJump * timerJump * max_jupm ) + max_jupm ;
    gY += yInitJump + (legs_width );


    printf("dy = %f \t gY %f  \t size %f  init %f\t \n", dy, gY ,timerJump , yInitJump );

    if(timerJump > 1.0){
        junping = 0;
        timerJump = -1;
    }

}

int Player::hasJumping() {return junping;}
