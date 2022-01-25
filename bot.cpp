#include "includes/bot.h"

Player *Bot::botCollision(tuple<GLfloat, GLfloat> position){
  if (_bot->live() > 0 && _bot->playerCollision(position)){
    return _bot;
  }
}

void Bot::rotine(Collision *obstacles, Player* p, GLdouble deltaTime){


  string direction = "right";

  if (_bot->getFacing() == -1)direction = "left";


  Surface *collision = obstacles->detectCollision(_bot->getSurface(), direction);
  Surface *floor = obstacles->hasFloor(_bot->getSurface());
  if (collision != NULL || floor == NULL){
    _bot->invertFacing();
    // collision->changeColor();
    // _bot->moveInX((_bot->getSurface()->getWidth())  * _bot->getFacing() * deltaTime);
    // _bot->moveSurfaceInX((_bot->getSurface()->getWidth()) * _bot->getFacing() * deltaTime);
  }
 
  _bot->moveInX(0.1 * _bot->getFacing() * deltaTime);
  _bot->moveSurfaceInX(0.1 * _bot->getFacing() * deltaTime);


  // Posiciona a arma do bot para o personagem
  tuple<GLfloat, GLfloat> pointer = p->getPos();
  _bot->moveArm2(get<1>(pointer), get<0>(pointer));
  float clock = deltaTime;
  if(deltaTime < 10) clock = 1000;
  time_shot += 1/clock;
  if(time_shot > MAX_TIME_SHOT){    
      _bot->shootGun();
      time_shot = 0;
    }
  if(_bot->getShot() != NULL) {
    Shot* shot = _bot->getShot();
    shot->draw();
    _bot->moveShot(deltaTime, obstacles);
    // shot->move(deltaTime);

    // Player* bot = world.checkBotsCollision(shot->getPos());
      // shot->draw();
      if(p->playerCollision(shot->getPos())){
         p->decrementLive();
      }
  }

}

void Bot::checkKiledPlayer(Player* p){
  if(collisionS2S(_bot->getSurface(), p->getSurface())){
    cout << "+++Passoooo  Mata personagem++++\n";
    p->decrementLive();
  }
}
