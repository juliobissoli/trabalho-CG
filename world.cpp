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

  // inicializa o matriz de objetos
  for (size_t i = 0; i < MAX_VIEW_Y; i++){
    for (size_t j = 0; j < MAX_VIEW_X; j++){
      /* code */
      mat_colision[i][j] = NULL;
    }
  }
  
  // Iniciliaza as superficies
  for (int i = 0; i < 2; i++){
    Surface *s = new Surface(_test[i][0], _test[i][1], _test[i][2], _test[i][3]);
    _surfaces.push_back(s);

    setSurfaceInMat(mat_colision, s);
  }

  // printMat(mat_colision);
};

void World::setSurfaceInMat(Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y], Surface *s){
  int x_init = (int)s->getLeft();
  int x_end = (int)s->getRight();

  int y_init = (int)s->getBooton();
  int y_end = (int)s->getTop();

  if(x_init < 0) x_init = 0;
  if(x_end > MAX_VIEW_X) x_end = MAX_VIEW_X;

  if(y_init < 0) x_init = 0;
  if(y_end > MAX_VIEW_Y) y_end = MAX_VIEW_Y;

  cout << "==== Range block ====== \n";
  cout << "[" << x_init << ", " << y_init << "]\n";
  cout << "[" << x_end  << ", " << y_end << "]\n";
  cout << "x_init - x_end = " <<  x_init - x_end << "\n";
  cout << "y_init - y_end = " <<  y_init - y_end << "\n";
  for (size_t i = y_init; i < y_end; i++){
    for (size_t j = x_init; j < x_end; j++){
        if(x_init == j || x_end == j)  cout << "insere [" << j  << ", " << i << "]\n";
        if(y_init == i || y_end == i)  cout << "insere [" << j  << ", " << i << "]\n";
        mat_colision[j][i] = s;
    }
  }

}

void World::printMat(Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y]){
  for (size_t i = 0; i < MAX_VIEW_Y; i++){
    for (size_t j = 0; j < MAX_VIEW_X; j++){
      /* code */
      // if( mat_colision[i][j] == NULL) cout << "_";
      // else cout << "[" << i << ", " << j<< "]\n";

       if( mat_colision[i][j] != NULL) cout << "[" << i << ", " << j<< "] \t";
       
    }
    // cout << "\n";
  }
  cout << "\n";
}

Surface* World::detectCollisionLeft(Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y], Surface* s){
  int x = (int)s->getRight();
  int y = (int)s->getTopCenter();
  
  if(x < 0) x = 0;
  if(x > MAX_VIEW_X) x = MAX_VIEW_X;

  if(y < 0) y = 0;
  if(y > MAX_VIEW_X) y = MAX_VIEW_X;


  Surface* item = mat_colision[x][y];
  
  cout << "Colisao em [" << x << "," << y  << "]\n";
  if(item != NULL) cout << "********** ACHOOOOO00 \n";
  
  Surface* teste = mat_colision[87][30];
  if(teste != NULL) cout << "acho um item \n";
  else cout << "ta muito doido \n"; 
  
  return item;
}


void World::draw(){
  surface->draw();
  for (auto s : _surfaces) {
    s->draw();
    // drawCircle(s->getTop(), s->getTop());
  }
}

// void World::desenhaRef(){
//   glPushMatrix();
//   glTranslatef(gX, gY, 0);
//   circle(5, 0.5, 0.5, 0.5);
//   glPopMatrix();
// }

void World::moveInX(GLfloat dx)
{
  int unit = MOVE_UNIT;
  gX += (dx * unit);
  surface->resetX(gX);
  for (auto s : _surfaces)
  {
    s->traslateX(dx * unit);
  }
}

// float World::getLeft(){
//     return gX - size_bloc/2;
// };

// World::~World() {}