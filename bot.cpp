#include "includes/bot.h"

Player *Bot::botCollision(tuple<GLfloat, GLfloat> position)
{
  if (_bot->live() > 0 && _bot->playerCollision(get<0>(position), get<1>(position)))
  {
    return _bot;
  }
}

void Bot::rotine(Collision *obstacles)
{

  string direction = "right";

  if (_bot->getFacing() == -1)direction = "left";
 
  Surface *collision = obstacles->detectCollision(_bot->getSurface(), direction);
  _bot->moveInX(0.5 * _bot->getFacing());
  _bot->moveSurfaceInX(0.5 * _bot->getFacing());

  if (collision != NULL){
  _bot->invertFacing();
  collision->changeColor();
  _bot->moveInX((_bot->getSurface()->getWidth())  * _bot->getFacing());

  _bot->moveSurfaceInX((_bot->getSurface()->getWidth()) * _bot->getFacing());

  }
}

void checkKiledPlayer(Player* p){
  
}
