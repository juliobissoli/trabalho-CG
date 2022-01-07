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
    glTranslatef(0 ,  body_height, 0);
    glRotatef(angle, 0, 0, 1);
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
    double positionX = gX + (arm_width * cos(gAngleArm * M_PI / 180));
    double positionY = gY + (body_height /2) + arm_height / 2 +  (arm_width * sin(gAngleArm * M_PI / 180));
    
    return new Shot(positionX, positionY, gAngleArm);
}

void Player::moveArm2(GLfloat dy, GLfloat dx){

    float y =  dy - yCenter;
    float x =  dx - xCenter;

    float theta = atan (y/x) * 180 / M_PI;
    if(theta < 45  && theta > -45 ){
        gAngleArm = theta;
    }
}
