#include "../includes/world.h"

#include <cstdio>
#include <math.h>
#define MOVE_UNIT 1


void World::drawCircle(GLfloat x, GLfloat y){
  glPushMatrix();
  glTranslatef(x, y, 0);
  circle(3, 0.115, 0.30, 0.103);
  glPopMatrix();
}

void World::drawSky(){
  glPushMatrix();
  glTranslatef(gX + (_max_x  / 2), gY, 0);
  rectangle(_max_y, _max_x, 0.0, 0.0, 1.0);
  glPopMatrix();
}


void World::build(  vector<tuple<double,double,double,double>> recs, 
                    vector<tuple<double,double,double>> circles,
                    float max_width,
                    float max_height ){
  cout << "=======Build do mundo======= \n";
  
  // Iniciliaza as superficies
  for (auto r : recs){
    if((GLfloat)get<0>(r) > -1 && (GLfloat)get<1>(r) > -1){

      Surface *s = new Surface((GLfloat)get<0>(r), (GLfloat)get<1>(r), (GLfloat)get<2>(r), (GLfloat)get<3>(r));
      _surfaces.push_back(s);
    }
  }

  _max_x = max_width;
  _max_y = max_height;
  _obstacles = new Collision((int)_max_x, (int)_max_y);

  _obstacles->build(_surfaces);
  
   for (auto c : circles){
    if((GLfloat)get<0>(c) > -1 && (GLfloat)get<1>(c) > -1){
        Bot* bot = new Bot((GLfloat)get<0>(c), (GLfloat)get<1>(c), ((float)get<2>(c) * 2.3));
      _bots.push_back(bot);

    }
  }

};


void World::draw(){
  // surface->draw();
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    
  drawSky();
  for (auto s : _surfaces) {
    s->draw();
  }

  for(auto b : _bots){
    if(b != NULL && b->live() > 0) {
      b->rotine(_obstacles, _player_ref, deltaTime);
      b->checkKiledPlayer(_player_ref);
      b->draw();
    }
  }

  cout << "desenha mund\n";
}


void World::moveInX(GLfloat dx){
  if(_obstacles->finishWordPlayer(dx, 4.0)) return;
  int unit = _player_ref->getMoveUnit();
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
  if(item != NULL) return true;
  return false;
}

bool World::finishWord(Surface* s){
  return _obstacles->finishWord(s);
}