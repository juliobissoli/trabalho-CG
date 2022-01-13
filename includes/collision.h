#ifndef COLLISION_H
#define COLLISION_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

#include "surface.h"


#include <iostream>
#include <vector>
#include <set>
#include<tuple>

#define MAX_VIEW_X 1500
#define MAX_VIEW_Y 500
  
using namespace std;

class Collision {

    Surface* _objStatics[MAX_VIEW_X][MAX_VIEW_Y];
    void setSurfaceInMat( Surface *s);
    Surface* _floor;
    // GLfloat gX;
    // GLfloat gY;
    // vector<vector<float>> matrix(float, vector<float>);
    // std::vector<std::vector<float> > matrix (float(2), std::vector<float>(4));
    

    private:
      tuple<int, int> handleeGetPointer(Surface* s, string x_direction, string y_direction  );
    
    public:
      Collision(){
        _floor = new Surface(0,0, MAX_VIEW_X, 2);
      }

      // Monta o array de superficies (obstáculos); 
    void build(vector<Surface*> surfaces);
    void printMat();
    Surface* detectCollision(Surface* s, string direction);
    
    Surface* hasFloor(Surface* s);

};

#endif /*COLLISION_H*/