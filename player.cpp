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
    // _surface->draw();
    Player::drawBody(x, y);
    Player::drawArm(x,y, angle);
    Player::drawHeader(x,y);
    Player::drawLegs(x,y);
    // Player::drawRef(x,y);
    glPopMatrix();

}

void Player::moveInX(GLfloat dx){
    int unit = MOVE_UNIT;
    gX += (dx * unit);
    // printf("Move player x =>\t %f \n", gX);
}
void Player::moveSurfaceInX(GLfloat dx){
    int unit = MOVE_UNIT;
    _surface->traslateX(dx * unit);
    // printf("Move player x =>\t %f \n", gX);
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

void Player::jump(GLdouble clock, Collision* collision){
    cout << "Jump " << _surface->getBooton() << "\n";

    if(clock <= 0) return;


    Surface* top_collision = collision->detectCollision(_surface, "top");
    if(top_collision != NULL){
        cout << "ta aaqui\n";
        junping = 0;
        return;
    }
        // float dy = -(timerJump * timerJump) + 2*timerJump ;

        if(clock <= 10) clock = 970;

        timerJump += (1 / clock );
    
        float max_jupm = (body_height + arm_height + legs_height) * 2;

        junping = 1;
        
        // gY = (dy *  gY ) + yInitJump;

        float aux = -(timerJump * timerJump * max_jupm ) + max_jupm ;
        aux += yInitJump ;
        _surface->resetY(aux);
        gY = _surface->getBooton() + (legs_height );

        
        Surface* floor = collision->hasFloor(_surface);
        if(timerJump > 0.0 && floor != NULL){
            junping = 0;
            timerJump = -1;
            yInitJump = floor->getBooton();

             _surface->resetY(floor->getBooton());
            gY = floor->getTop() + legs_height;
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

void Player::moveInY(GLfloat dy){
     int unit = MOVE_UNIT;
    gY += (dy * unit);
    _surface->resetY(gY - legs_height);
}

