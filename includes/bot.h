#ifndef BOT_H


#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <vector>

#include "player.h"
#include "collision.h"

#define MAX_TIME_SHOT 10


using namespace std;

class Bot{
    Player* _bot;
    string rotina; //definir com montar a rotina de o bot
    float time_shot;
private:
    /* data */
public:
    Bot(GLfloat x_init, GLfloat y_init, float size){
         _bot = new Player(x_init, y_init, size,"red");
    }
    ~Bot();

    void draw(){_bot->Desenha();}
    Player* player(){return _bot;}
    int live(){return _bot->live();}
    void moveInX(GLfloat dx){
        _bot->moveInX(dx);
        _bot->moveSurfaceInX(dx);
        time_shot = 0;
    }

    Player* botCollision(tuple<GLfloat, GLfloat> position);
    void rotine(Collision* obstacles, Player* p, GLdouble curTime);
    void checkKiledPlayer(Player* p);
};



#endif  /*BOT_H*/
