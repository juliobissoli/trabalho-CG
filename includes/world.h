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

using namespace std;

class World
{
  //Variáveis de posicionamento e dimensão do mundo.
  GLfloat gX;
  GLfloat gY;
  GLfloat _max_x;
  GLfloat _max_y;

  //Variáveis de conponentes que compoem o mundo
  Collision *_obstacles;
  vector<Surface *> _surfaces;
  vector<Bot *> _bots;
  Player *_player_ref;
  GLdouble _deltaTime;

  // Variáveis para modo de jogo
  bool _run_rotine_bot;
  bool _collision_robot_kills;

private:
  void drawCircle(GLfloat x, GLfloat y);
  void desenhaRef();
  void setSurfaceInMat(Surface *mat_colision[MAX_VIEW_X][MAX_VIEW_Y], Surface *s);
  void drawSky();

  tuple<int, int> handleeGetPointer(Surface *s, string x_direction, string y_direction);

public:
  World()
  {
    gX = 0;
    gY = 0;
    _max_x = MAX_VIEW_X;
    _max_y = MAX_VIEW_Y;
    _deltaTime = 0.0;

    _run_rotine_bot = true;
    _collision_robot_kills = true;
  }

  void build(vector<tuple<double, double, double, double>> recs,
             vector<tuple<double, double, double>> circles,
             float max_width,
             float max_height);

  void draw();
  void destroi();
  void moveInX(GLfloat dx);
  void setDeltaTime(GLdouble deltaTime) { _deltaTime = deltaTime; }
  void setPlayer(Player *p) { _player_ref = p; }
  bool checkObstacleCollision(Surface *s);
  bool finishWord(Surface *s);

  GLfloat getWidth() { return _max_x; };
  GLfloat getHeight() { return _max_y; };

  vector<Surface *> getSurfaces() { return _surfaces; };
  Player *checkBotsCollision(tuple<GLfloat, GLfloat> position);
  Surface *obstacleCollision(Surface *s, string direction) { return _obstacles->detectCollision(s, direction); };
  Collision *getObstacles() { return _obstacles; }
  Surface *hasFloor(Surface *s) { return _obstacles->hasFloor(s); }
  vector<Bot *> getBots();
  Player *getPlayer(Player *p) { return _player_ref; }

  void changeModeRinRotineBot(){_run_rotine_bot =  !_run_rotine_bot;}
  void changeModeCollisionRobotKills(){_collision_robot_kills =  !_collision_robot_kills;}};

#endif /*WORLD_H*/