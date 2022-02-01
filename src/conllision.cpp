#include "../includes/collision.h"

#include <cstdio>
#include <math.h>

void Collision::build(vector<Surface *> surfaces)
{
  for (auto s : surfaces)
  {
    setSurfaceInMat(s);
  }
};

bool Collision::finishWord(Surface *s)
{
  int x = s->getXCenter();
  int y = s->getYCenter();
  if (x > _max_x || x < 0 || y > _max_y || y < 0)
    return true;
  else
    return false;
}

void Collision::setSurfaceInMat(Surface *s)
{
  int x_init = (int)s->getLeft();
  int x_end = (int)s->getRight();

  int y_init = (int)s->getBooton();
  int y_end = (int)s->getTop();

  if (x_init < 0)
    x_init = 0;
  if (x_end > _max_x)
    x_end = _max_x - 1;

  if (y_init < 0)
    x_init = 0;
  if (y_end > _max_y)
    y_end = _max_y - 1;

  for (int i = y_init; i < y_end; i++)
  {
    for (int j = x_init; j < x_end; j++)
    {
      _objStatics[j][i] = s;
    }
  }
}

void Collision::printMat()
{
  for (size_t i = 0; i < _max_y; i++)
  {
    for (size_t j = 0; j < _max_x; j++)
    {
      if (_objStatics[i][j] != NULL)
        cout << "[" << i << ", " << j << "] \t";
    }
  }
  cout << "\n";
}

Surface *Collision::detectCollision(Surface *s, string direction)
{

  Surface *item;
  if (direction == "center")
  {
    item = handleAvaliatePointer(s, "center", "center");
    if (item != NULL)
      return item;
  }

  if (direction == "left" || direction == "right")
  {
    vector<string> other_axis = {"top", "center"};
    for (auto dir : other_axis)
    {
      item = handleAvaliatePointer(s, direction, dir);
      if (item != NULL)
        return item;
    }
  }
  if (direction == "top" || direction == "booton")
  {
    vector<string> other_axis = {"center"};
    for (auto dir : other_axis)
    {
      item = handleAvaliatePointer(s, dir, direction);
      if (item != NULL)
        return item;
    }
  }
  return NULL;
}

Surface *Collision::handleAvaliatePointer(Surface *s, string x_direction, string y_direction)
{

  tuple<int, int> pointer = handleeGetPointer(s, x_direction, y_direction);

  int x = get<0>(pointer);
  int y = get<1>(pointer);

  Surface *item = _objStatics[x][y];

  return item;
}

tuple<int, int> Collision::handleeGetPointer(Surface *s, string x_direction, string y_direction)
{

  int x = 0;
  int y;

  if (x_direction == "right")
    x = (int)s->getRight();
  if (x_direction == "left")
    x = (int)s->getLeft();
  if (x_direction == "center")
    x = (int)s->getXCenter();

  if (y_direction == "top")
    y = (int)s->getTop();
  if (y_direction == "booton")
    y = (int)s->getBooton();
  if (y_direction == "center")
    y = (int)s->getYCenter();

  x = x - (int)_x_ref;
  if (x < 0)
    x = 0;
  if (x > _max_x)
    x = _max_x;

  if (y < 0)
    y = 0;
  if (y > _max_x)
    y = _max_x;

  tuple<int, int> pointer = make_tuple(x, y);

  return pointer;
}

Surface *Collision::hasFloor(Surface *s)
{
  float min_y = s->getBooton();
  if (min_y < 0.0)
    return _floor;

  else
    return detectCollision(s, "booton");
}

bool Collision::inpactPointer(tuple<GLfloat, GLfloat> pointer)
{

  int x = (int)get<0>(pointer);
  int y = (int)get<1>(pointer);

  if (x < 0 || y < 0 || x > _max_x || y > _max_x)
    return true;

  Surface *item = _objStatics[(x - (int)_x_ref)][y];

  if (item != NULL)
    return true;
  else
    return false;
}

bool collisionS2S(Surface *s1, Surface *s2)
{

  //Se o centro da superficie s1 estiver interno a superficie s2 returna true
  if (s1->getXCenter() <= s2->getRight() &&
      s1->getXCenter() >= s2->getLeft() && 
      s1->getYCenter() <= s2->getTop() && 
      s1->getYCenter() >= s2->getBooton())
    return true;

  //Se o ponto central mais a esquerda da superficie s1 estiver interno a superficie s2 returna true
  if (s1->getLeft() <= s2->getRight() && 
      s1->getLeft() >= s2->getLeft() &&
      s1->getYCenter() <= s2->getTop() &&
      s1->getYCenter() >= s2->getBooton())
    return true;

  //Se o ponto central mais a direita da superficie s1 estiver interno a superficie s2 returna true
  if (s1->getRight() <= s2->getRight() &&
      s1->getRight() >= s2->getLeft() &&
      s1->getYCenter() <= s2->getTop() &&
      s1->getYCenter() >= s2->getBooton())
    return true;

  //Se o ponto central mais a cima da superficie s1 estiver interno a superficie s2 returna true
  if (s1->getXCenter() <= s2->getRight() &&
      s1->getXCenter() >= s2->getLeft() &&
      s1->getTop() <= s2->getTop() &&
      s1->getTop() >= s2->getBooton())
    return true;

  //Se o ponto central mais a baixo da superficie s1 estiver interno a superficie s2 returna true
  if (s1->getXCenter() <= s2->getRight() &&
      s1->getXCenter() >= s2->getLeft() &&
      s1->getBooton() <= s2->getTop() &&
      s1->getBooton() >= s2->getBooton())
    return true;
  
  //Retorna false se nao colidir em nenhum dos casos. 
  return false;
}

bool Collision::finishWordPlayer(float facing, float x_gab_start)
{
  if (facing < 0 && _x_ref < -_max_x - x_gab_start)
    return true;
  if (facing > 0 && _x_ref > 0 + x_gab_start)
    return true;
  return false;
}
