#include "includes/bot.h"

Player* Bot::botCollision(tuple<GLfloat, GLfloat> position){
    if(_bot->live() > 0 && _bot->playerCollision(get<0>(position), get<1>(position))){
      return _bot;
    }
}