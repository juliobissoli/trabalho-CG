#ifndef BOT_H


#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <vector>

#include "player.h"
#include "collision.h"

using namespace std;

class Bot{
    Player* _bot;
    string rotina; //definir com montar a rotina de o bot

private:
    /* data */
public:
    Bot(GLfloat x_init, GLfloat y_init){
         _bot = new Player(x_init, y_init, "red");
    }
    ~Bot();

    void draw(){_bot->Desenha();}
    Player* player(){return _bot;}
    int live(){return _bot->live();}
    void moveInX(GLfloat dx){
        _bot->moveInX(dx);
        _bot->moveSurfaceInX(dx);
    }

    Player* botCollision(tuple<GLfloat, GLfloat> position);
    void rotine(Collision* obstacles, Player* p);
    void checkKiledPlayer(Player* p);
};



#endif  /*BOT_H*/
