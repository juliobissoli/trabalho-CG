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

void World::drawSky(){
  glPushMatrix();
  glTranslatef(gX + (_max_x  / 2), gY, 0);
  // circle(3, 0.115, 0.30, 0.103);
  rectangle(_max_y, _max_x, 0.0, 0.0, 0.5);
  glPopMatrix();
}

// void World::build(float _test[2][4]){
//   //  drawObstacles(gX, gY);
//   cout << "=======Build do mundo======= \n";

//   // _player_ref = p;
//   // Iniciliaza as superficies
//   for (int i = 0; i < 4; i++){
//     Surface *s = new Surface(_test[i][0], _test[i][1], _test[i][2], _test[i][3]);
//     _surfaces.push_back(s);
//   }

//   _obstacles->build(_surfaces);

// };

void World::build(){
  //  drawObstacles(gX, gY);
    read.loadinFile("/home/motora/UFES/2021-2/CG/trabalho-CG/arena_teste.svg");

  // read.loadinFile("/home/jcsbissoli/UFES/2021-2/CG/Trabalho/T1/arena_teste.svg");
  read.printTeste();

  cout << "=======Build do mundo======= \n";
  vector<tuple<double,double,double,double>> recs = read.getRecs();
  // _player_ref = p;
  // Iniciliaza as superficies
  for (auto r : recs){
    if((GLfloat)get<0>(r) > -1 && (GLfloat)get<1>(r) > -1){

      Surface *s = new Surface((GLfloat)get<0>(r), (GLfloat)get<1>(r), (GLfloat)get<2>(r), (GLfloat)get<3>(r));
      _surfaces.push_back(s);
    }
  }

  //Remover esse teste
  // recs = read.getRecFake();

  //  for (auto r : recs){
  //    if((GLfloat)get<0>(r) > -1 && (GLfloat)get<1>(r) > -1){

  //      Surface *s = new Surface((GLfloat)get<0>(r), (GLfloat)get<1>(r), (GLfloat)get<2>(r), (GLfloat)get<3>(r));
  //      s->changeColor();
  //      _surfaces.push_back(s);
  //    }
  //  }

  _max_x = read.getWidth();
  _max_y = read.getHeight();
    // cout << "tamanho da matriz ["<< _max_x << ", " << _max_y << "]\n";
  _obstacles = new Collision((int)_max_x, (int)_max_y);

  _obstacles->build(_surfaces);
  _player_ref = new Player(30.0, 0.0, "green", _obstacles);


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
    if(b->live() > 0) {
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
  // _obstacles->inpactPointer(position);
  if(item != NULL) return true;
  return false;
}

bool World::finishWord(Surface* s){
  // int x = s->getXCenter();
  // int y = s->getYCenter();

  // if(x > _max_x || x < 0 || y > _max_Y || y < 0) return true;
  // else return false;

  return _obstacles->finishWord(s);
}



// float World::getLeft(){
//     return gX - size_bloc/2;
// };

// World::~World() {}