#include "./includes/collision.h"

#include <cstdio>
#include <math.h>




void Collision::build(vector<Surface*> surfaces){
  cout << "=======Build do colisão======= \n";
    for (auto s : surfaces) {
        setSurfaceInMat(s);
    }


  // printMat(mat_colision);
};

void Collision::setSurfaceInMat(Surface *s){
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

  for (int i = y_init; i < y_end; i++){
    for (int j = x_init; j < x_end; j++){
        if(x_init == j || x_end == j)  cout << "insere [" << j  << ", " << i << "]\n";
        if(y_init == i || y_end == i)  cout << "insere [" << j  << ", " << i << "]\n";
        _objStatics[j][i] = s;
    }
  }

}

void Collision::printMat(){
  for (size_t i = 0; i < MAX_VIEW_Y; i++){
    for (size_t j = 0; j < MAX_VIEW_X; j++){
       if( _objStatics[i][j] != NULL) cout << "[" << i << ", " << j<< "] \t";
       
    }
    // cout << "\n";
  }
  cout << "\n";
}

Surface* Collision::detectCollision(Surface* s, string direction){

  tuple <int, int> pointer;
  
  if(direction == "left" || direction == "right") pointer = handleeGetPointer(s, direction, "center");
  if(direction == "top" || direction == "booton") pointer = handleeGetPointer(s, "center", direction);

  int x = get<0>(pointer);
  int y = get<1>(pointer);


  Surface* item = _objStatics[x][y];
  
  // cout << "Colisao em: |"<< direction << " center| -[" <<   x << "," << y  << "]\n";
  // if(item != NULL) cout << "********** ACHOOOOO00 \n";
  
  
  return item;
}

 tuple<int, int> Collision::handleeGetPointer(Surface* s, string x_direction, string y_direction ){
   
  int x; 
  int y; 

  if(x_direction == "right") x = (int)s->getRight();
  if(x_direction == "left") x = (int)s->getLeft();
  if(x_direction == "center") x = (int)s->getXCenter();

  if(y_direction == "top") y = (int)s->getTop();
  if(y_direction == "booton") y = (int)s->getBooton();
  if(y_direction == "center") y = (int)s->getYCenter();
  
  if(x < 0) x = 0;
  if(x > MAX_VIEW_X) x = MAX_VIEW_X;

  if(y < 0) y = 0;
  if(y > MAX_VIEW_X) y = MAX_VIEW_X;

  tuple <int, int> pointer = make_tuple(x,y);

  return pointer;
}

Surface* Collision::hasFloor(Surface* s){
    float min_y = s->getBooton();
    if(min_y < 0.0) return _floor;

    else return detectCollision(s, "booton");
}

// float World::getLeft(){
//     return gX - size_bloc/2;
// };

// World::~World() {}