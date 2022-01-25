#include "./includes/world.h"

#include <cstdio>
#include <math.h>
#define MOVE_UNIT 1


void World::drawCircle(GLfloat x, GLfloat y){
  glPushMatrix();
  glTranslatef(x, y, 0);
  circle(3, 0.115, 0.30, 0.103);
  glPopMatrix();
}

void World::build(float _test[2][4]){
  //  drawObstacles(gX, gY);
  cout << "=======Build do mundo======= \n";

  // _player_ref = p;
  // Iniciliaza as superficies
  for (int i = 0; i < 4; i++){
    Surface *s = new Surface(_test[i][0], _test[i][1], _test[i][2], _test[i][3]);
    _surfaces.push_back(s);
  }

  _obstacles->build(_surfaces);

};


void World::draw(){
  // surface->draw();
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    

  for (auto s : _surfaces) {
    s->draw();
  }

  for(auto b : _bots){
    if(b->live() > 0) {
      b->rotine(_obstacles, _player_ref, deltaTime);
      b->checkKiledPlayer(_player_ref);
      b->draw();
    }
  }
}


void World::moveInX(GLfloat dx){
  if(_obstacles->finishWordPlayer(dx, 400.0)) return;
  int unit = MOVE_UNIT;
  gX += (dx * unit);
  _obstacles->resetXRef(gX);
  for (auto s : _surfaces){
    s->traslateX(dx * unit);
  }
  for(auto b : _bots){
    b->moveInX(dx * unit);
  }

}

Player* World::checkBotsCollision(tuple<GLfloat, GLfloat> position){
  
  for (auto b : _bots){
      Player* p = b->botCollision(position);
      if(b->live() > 0 && p != NULL){
        return p;
      }
    }
    return NULL;
}

bool World::checkObstacleCollision(Surface* s){
  
  Surface* item = _obstacles->detectCollision(s, "center");
  // _obstacles->inpactPointer(position);
  if(item != NULL) return true;
  return false;
}

bool World::finishWord(Surface* s){
  // int x = s->getXCenter();
  // int y = s->getYCenter();

  // if(x > MAX_VIEW_X || x < 0 || y > MAX_VIEW_Y || y < 0) return true;
  // else return false;

  return _obstacles->finishWord(s);
}



// float World::getLeft(){
//     return gX - size_bloc/2;
// };

// World::~World() {}