#include "./includes/player.h"
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

void Player::drawLegs(GLint x, GLint y){
    glPushMatrix();
        glTranslatef(x, y, 0);
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
    _surface->draw();
    Player::drawBody(x, y);
    Player::drawArm(x,y, angle);
    Player::drawHeader(x,y);
    Player::drawLegs(x,y);
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
        move_init = body_width / 3;
}

void Player::moveInX(GLfloat dx){
    int unit = move_init;
    gX += (dx * unit);
}

void Player::moveInY(GLfloat dy){
     int unit = move_init;
    gY += (dy * unit);
    _surface->resetY(gY - (legs_height * 2));
}


void Player::moveSurfaceInX(GLfloat dx){
    int unit = move_init;
    _surface->traslateX(dx * unit);
}

void Player::handleGravity(float deltaTime, Collision* obstacles){

    if(obstacles->hasFloor(this->_surface) == NULL){
        this->moveInY(-0.1 * deltaTime);
    }
   
}


void Player::moveArm(GLfloat dy){
    int unit = move_init;
    if((gAngleArm < 45 && dy > 0) || (gAngleArm > -45 && dy < 0)){
        gAngleArm += (dy * unit);
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
    //    Player* b =  world.checkBotsCollision(_shot->getPos());
    Surface* obstacle = obstacles->detectCollision(_shot->getSurface(), "center");


    if (
        obstacle != NULL ||
        obstacles->finishWord(_shot->getSurface())
        ) {
            delete _shot;
            _shot = NULL;
        }
      else {
       _shot->move(deltaTime * 0.01);
      }
      // delete b; b = NULL;
   }
     
     
}
void Player::moveArm2(GLfloat dy, GLfloat dx){

    
    // if(dx < gX)gFacing  = -1;
    // else  gFacing  = 1;
    // printf("gX= %f \t dX %f \t gFacing %d\n", gX, dx, gFacing);
    float y =  dy - gY + (body_height / 2);
    float x =  dx - gX + (body_width / 2);


    float theta = atan (y/x) * 180 / M_PI;
    if(theta < 45  && theta > -45 ){
        gAngleArm = theta * gFacing;
    }
}

void Player::jump(GLdouble clock, Collision* collision){

    if(clock <= 0) return;
    
    //Verica se o personagem caiu de uma plataforma sem pular
    if(_surface->getBooton() <= 0 && junping == 0)yInitJump = 0;

    Surface* top_collision = collision->detectCollision(_surface, "top");
    // Surface* center_collision = collision->detectCollision(_surface, "center");
    if(top_collision != NULL){
        // cout << "ta aaqui\n";
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
        _floor = NULL;
        // gY = (dy *  gY ) + yInitJump;

        float aux = -(timerJump * timerJump * max_jupm ) + max_jupm ;
        aux += yInitJump ;
        _surface->resetY(aux);
        gY = aux + legs_height;
        // _surface->getTop() + (legs_height);
        cout << "pulo gY = " << gY << endl;
        
        Surface* floor = collision->hasFloor(_surface);
        if(timerJump > 0.0 && floor != NULL){

            junping = 0;
            timerJump = -1;
            yInitJump = floor->getTop();
            _floor = floor;
            
            cout << "Flor "<< floor->getTop() << endl;
            
            gY = floor->getTop() + legs_height;
            _surface->resetY(floor->getTop());
            // cout << "Acho o chao " << gY << endl;
        }
    

}

void Player::stopJump(){
    if(timerJump > 0){
        junping = 0;
        timerJump = -1;
        yInitJump = _surface->getBooton() + (legs_height);
        // gY - (legs_width + yInitJump);
    }
};


int Player::hasJumping() {return junping;}




bool Player::playerCollision(tuple<GLfloat, GLfloat> pointer){
    return _surface->isInternal(get<0>(pointer),get<1>(pointer));
}
