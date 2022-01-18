#include "./includes/world.h"

#include <cstdio>
#include <math.h>
#define MOVE_UNIT 1


void World::drawCircle(GLfloat x, GLfloat y){
  cout << "desenha ref [x " << x << ", y" << y << "]\n";
  glPushMatrix();
  glTranslatef(x, y, 0);
  circle(3, 0.115, 0.30, 0.103);
  glPopMatrix();
}

void World::build(float _test[2][4], Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y]){
  //  drawObstacles(gX, gY);
  cout << "=======Build do mundo======= \n";

  
  // Iniciliaza as superficies
  for (int i = 0; i < 2; i++){
    Surface *s = new Surface(_test[i][0], _test[i][1], _test[i][2], _test[i][3]);
    _surfaces.push_back(s);

  }

};


void World::draw(){
  // surface->draw();
  for (auto s : _surfaces) {
    s->draw();
  }

  for(auto b : _bots){
    if(b->live() > 0) b->draw();
  }


  // if(oponente != NULL){

  //   if(oponente->live() > 0){
  //     oponente->Desenha();
  //     // cout << "DESENHA OPONENTE \n";
  //   }
  //   else {
  //     delete oponente;
  //     oponente = NULL;
  //   }
  // }
}


void World::moveInX(GLfloat dx){
  int unit = MOVE_UNIT;
  gX += (dx * unit);
  // surface->resetX(gX);
  for (auto s : _surfaces){
    s->traslateX(dx * unit);
  }
  for(auto b : _bots){
    b->moveInX(dx * unit);
  }
  // oponente->moveInX(dx);
  // oponente->moveSurfaceInX(dx);
}

Player* World::checkBotsCollision(tuple<GLfloat, GLfloat> position){
  
  for (auto b : _bots){
    Player* p = b->botCollision(position);
    if(b->live() > 0 && p != NULL){
      return p;
    }
    // if(b == NULL) return NULL;
    // if(b->player()->playerCollision(get<0>(position), get<1>(position)))
    //   return b->player();
    }
    return NULL;
}


// float World::getLeft(){
//     return gX - size_bloc/2;
// };

// World::~World() {}