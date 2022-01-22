#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <tuple>

#include "world.h"
#include "polygon.h"
#include "surface.h"
#include "player.h"
#include "bot.h"
#include "collision.h"


#define size_bloc 50.0 //remover tamanho so para teste
#define MAX_VIEW_X 1500
#define MAX_VIEW_Y 800
  
using namespace std;

class World {

    GLfloat gX;
    GLfloat gY;

    Collision* _obstacles;
    // Surface *surface; //remover isso apos resolver colizões
    // vector<vector<float>> matrix(float, vector<float>);
    // std::vector<std::vector<float> > matrix (float(2), std::vector<float>(4));
    vector<Surface*> _surfaces;
    vector<Bot*> _bots;
    Player* _player_ref;
    


    

    private:
      void drawCircle(GLfloat x, GLfloat y);
      void desenhaRef();
      void setSurfaceInMat(Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y], Surface *s);

      tuple<int, int> handleeGetPointer(Surface* s, string x_direction, string y_direction  );
    public:
      World(){
          gX = 0;
          gY = 0; 
          // oponente = new Player(300.0, 0.0, "red");
          _obstacles = new Collision();
          Bot* b1 = new Bot(300.0, 0);
          Bot* b2 = new Bot(700.0, 0);

          _bots.push_back(b1);
          _bots.push_back(b2);



          // surface =  new Surface( gX, gY, size_bloc, size_bloc);

      }

      // Monta o array de superficies (obstáculos); 
    void build(float _test[4][4], Player* p);
    void draw();
    vector<Surface*> getSurfaces(){return _surfaces;};
    void moveInX(GLfloat dx);
    Player* checkBotsCollision(tuple<GLfloat, GLfloat> position);
    bool checkObstacleCollision(Surface* s);
    bool finishWord(Surface* s);

    Surface* obstacleCollision(Surface* s, string direction){return _obstacles->detectCollision(s, direction);};
    Collision* getObstacles(){return _obstacles;}
    Surface* hasFloor(Surface* s){return _obstacles->hasFloor(s);}



};

#endif /*WORLD_H*/