#include "../includes/player.h"
#include <string>
#include <cmath>


using namespace std;


void Player::drawBody(GLint x, GLint y){
    glPushMatrix();
        glTranslatef(x, y, 0);
        rectangle(body_height, body_width,  get<0>(_body_color), get<1>(_body_color), get<2>(_body_color));
    glPopMatrix();
}


void Player::drawHeader(GLint x, GLint y){
    glPushMatrix();
        glTranslatef(x, y, 0);
        glTranslatef(0,  (body_height + radius_header), 0);
        circle(radius_header,get<0>(_body_color), get<1>(_body_color), get<2>(_body_color));
    glPopMatrix();
}

void Player::drawArm(GLint x, GLint y, GLint angle){
    glPushMatrix();
        glTranslatef(x,  0 , 0);
        glTranslatef(0 , y + (body_height /2), 0);
        glRotatef(angle, 0, 0, 1);
        glRotatef(90 + (90 * -gFacing), 0, 1, 0);
        glTranslatef(body_width / 2.0, 0,0);
        rectangle(arm_height, arm_width, 1.0, 1.0, 0.0);
    glPopMatrix();
}

void Player::drawLeg(GLint x, GLint y, int main_lag){
    glPushMatrix();
    glTranslatef(x, y, 0);
    // glTranslatef(x,  0 , 0);
    // glTranslatef(0 , y + body_height, 0);

    GLfloat angle = gAngleLeg % 45; 
    glRotatef(angle * gFacing * main_lag, 0, 0, 1);
    glTranslatef(0,  (-body_height + (body_height - legs_height)), 0);
    rectangle(legs_height, legs_width, get<0>(_body_color), get<1>(_body_color), get<2>(_body_color));
    glPopMatrix();
}

void Player::drawRef(GLint x, GLint y){
    glPushMatrix();
        glTranslatef(x, _surface->getBooton(), 0);
        circle(4, 0.5, 0.5, 0.5);
    glPopMatrix();
}

void Player::drawPlayer(GLint x, GLint y, GLint angle){
    
    glPushMatrix();
    // _surface->draw();
    Player::drawBody(x, y);
    Player::drawArm(x,y, angle);
    Player::drawHeader(x,y);
    Player::drawLeg(x,y, 1);
    Player::drawLeg(x,y, -1);
    // Player::drawRef(x,y);
    glPopMatrix();

    if (this->_shot != NULL){
        this-> _shot->draw();
      }
}

void Player::handleAjusteSize(){
        body_height  = height_player / 3; // 40.0;
        legs_height  = height_player / 3; //40.0 ;
        radius_header  = height_player / 3 / 2; //20.0;
        arm_height  = height_player /9; // 5.0;
        body_width  = height_player / 3; // 25.0;
        arm_width  = height_player / 3;  // 30.0;
        legs_width  = height_player / 9; // 10.0;
        move_unit = body_width / 3;
}

void Player::moveInX(GLfloat dx){
    int unit = move_unit;
    gX += (dx * unit);
    
    // printf("Move player x =>\t %f \n", gX);
}

void Player::moveInY(GLfloat dy){
     int unit = move_unit;
    gY += (dy * unit);
    _surface->resetY(gY - (legs_height * 2));
}


void Player::moveSurfaceInX(GLfloat dx){
    int unit = move_unit;
    _surface->traslateX(dx * unit);
    gAngleLeg += dx *  unit + body_width;

}

void Player::handleGravity(float deltaTime, Collision* obstacles){
       Surface* floor = obstacles->hasFloor(this->_surface);
    
    if(floor == NULL){
        this->moveInY(-0.3 * deltaTime);
    }
    else {
        if(this->_surface->getBooton() != floor->getTop() -1){
            gY = floor->getTop() + legs_height;
            _surface->resetY(floor->getTop() - 1);
        }
    }
   
}


Shot *Player::shootGun(){
    //Calcular onde esta a ponta da arma para indicar de onde o diro sairá
    //Multiplicando pela direção (gFacing) para corigir o sentindo  p onde o personagem esta aponado
    double positionX = gX + (gFacing * arm_width * cos(gAngleArm * M_PI / 180));
    double positionY = gY + (body_height /2) + arm_height / 2 +  (gFacing * arm_width * sin(gAngleArm * M_PI / 180));
    
     _shot = new Shot(positionX, positionY, gAngleArm, gFacing, arm_height);
    return _shot;
}


void Player::moveShot(float deltaTime, Collision* obstacles){
    if(_shot){
     Surface* obstacle = obstacles->detectCollision(_shot->getSurface(), "center");
     if ( obstacle != NULL || obstacles->finishWord(_shot->getSurface()) ) {
            delete _shot;
            _shot = NULL;
        }
      else {
       _shot->move(deltaTime * 0.2);
      }
   }
     
     
}
void Player::moveArm2(GLfloat dy, GLfloat dx){

    float y =  dy - gY; // + (body_height / 2);
    float x =  dx - gX; // + (body_width / 2);
    float theta = atan (y/x) * 180 / M_PI;
    if(theta < 45  && theta > -45 ){
        gAngleArm = theta * gFacing;
    }
}

void Player::moveArm(GLfloat dy){
    if (_last_y_mouse == 0){ _last_y_mouse = dy;}

    GLfloat deltaY = dy -_last_y_mouse;
    gAngleArm += deltaY * 0.3 * gFacing;

    if (this->gAngleArm > 45){    gAngleArm = 45;}
    if (this->gAngleArm < -45){    gAngleArm = -45;}

    _last_y_mouse = dy;

}


void Player::jump(GLdouble clock, Collision* collision){

    if(clock <= 0) return;
    
    //Verica se o personagem caiu de uma plataforma sem pular
    if(_surface->getBooton() <= 0 && junping == 0)yInitJump = 0;

    Surface* top_collision = collision->detectCollision(_surface, "top");
    // Surface* center_collision = collision->detectCollision(_surface, "center");
    if(top_collision != NULL){
        top_collision->changeColor();
        junping = 0;
        return;
    }
        // float dy = -(timerJump * timerJump) + 2*timerJump ;

        if(clock <= 10) clock = 300;
        // cout << "Jump " << clock << "\n";
        timerJump += 1 / ( clock);
        float max_jupm = (height_player) * 3;

        junping = 1;
        gAngleLeg = 44;
        // gY = (dy *  gY ) + yInitJump;

        float aux = -(timerJump * timerJump * max_jupm ) + max_jupm ;
        aux += yInitJump ;
        _surface->resetY(aux);
        gY = aux + legs_height;
        // _surface->getTop() + (legs_height);
        
        Surface* floor = collision->hasFloor(_surface);
        if(timerJump > 0.0 && floor != NULL){
            gAngleLeg = 0;
            junping = 0;
            timerJump = -1;
            yInitJump = floor->getTop();
            _floor = floor;
            
            cout << "Flor "<< floor->getTop() << endl;
            
            gY = floor->getTop() + (legs_height* 4);
            _surface->resetY(floor->getTop() + (legs_height * 3));
            // cout << "Acho o chao " << gY << endl;
        }
    

}

void Player::stopJump(){
    if(timerJump > 0){
        junping = 0;
        timerJump = -1;
        yInitJump = _surface->getBooton() + (legs_height);
        gAngleLeg = 0;
        // gY - (legs_width + yInitJump);
    }
};


int Player::hasJumping() {return junping;}




bool Player::playerCollision(tuple<GLfloat, GLfloat> pointer){
    return _surface->isInternal(get<0>(pointer),get<1>(pointer));
}
