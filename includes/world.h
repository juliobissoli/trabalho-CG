#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


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
#include "read_svg.h"


// #define size_bloc 50.0 //remover tamanho so para teste
// #define MAX_VIEW_X 300
// #define MAX_VIEW_Y 100
  
using namespace std;

class World {
    Read read;
    GLfloat gX;
    GLfloat gY;

    GLfloat _max_x;
    GLfloat _max_y;

    Collision* _obstacles;
    // Surface *surface; //remover isso apos resolver colizões
    // vector<vector<float>> matrix(float, vector<float>);
    // std::vector<std::vector<float> > matrix (float(2), std::vector<float>(4));
    vector<Surface*> _surfaces;
    vector<Bot*> _bots;
    Player* _player_ref;
    GLdouble _deltaTime;
    


    

    private:
      void drawCircle(GLfloat x, GLfloat y);
      void desenhaRef();
      void setSurfaceInMat(Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y], Surface *s);
      void drawSky();
      
      tuple<int, int> handleeGetPointer(Surface* s, string x_direction, string y_direction  );
    public:
      World(){
          gX = 0;
          gY = 0; 
          _max_x = MAX_VIEW_X;
          _max_y = MAX_VIEW_Y;
          // oponente = new Player(300.0, 0.0, "red");
          // _obstacles = new Collision((int)_max_x, (int)_max_y);
          // Bot* b1 = new Bot(110.0, 0.0, _obstacles);
          // Bot* b2 = new Bot(150.0, 0, _obstacles);
          

          // _bots.push_back(b1);
          // _bots.push_back(b2);
          _deltaTime = 0.0;


          // surface =  new Surface( gX, gY, size_bloc, size_bloc);

      }

      // Monta o array de superficies (obstáculos); 
    // void build(float _test[4][4]);
    void build();
    void draw();
    vector<Surface*> getSurfaces(){return _surfaces;};
    void moveInX(GLfloat dx);
    Player* checkBotsCollision(tuple<GLfloat, GLfloat> position);
    bool checkObstacleCollision(Surface* s);
    bool finishWord(Surface* s);

    Surface* obstacleCollision(Surface* s, string direction){return _obstacles->detectCollision(s, direction);};
    Collision* getObstacles(){return _obstacles;}
    Surface* hasFloor(Surface* s){return _obstacles->hasFloor(s);}
    vector<Bot*>getBots();

    void setDeltaTime(GLdouble deltaTime){_deltaTime = deltaTime;}
    Player* getPlayer(){return _player_ref;}


};

#endif /*WORLD_H*/