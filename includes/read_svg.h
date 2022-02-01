#include "tinyxml2.h"
#include <string>
#include <vector>
#include <tuple>

#ifndef READ_H

using namespace std;

class Read
{
  double gX;
  double gY;
  double gWidth;
  double gHeight;

  vector<tuple<double, double, double, double>> _rec_list;
  vector<tuple<double, double, double, double>> _rec_fake_list;
  vector<tuple<double, double, double>> _circ_list;
  tuple<double, double, double> _player_rec;

private:
  /* data */
  void _readingRectangle(tinyxml2::XMLElement *element);
  void _readingCircle(tinyxml2::XMLElement *element);
  double _ajusteY(double dy, double height);

public:
  Read()
  {
    gX = 0;
    gY = 0;
    gWidth = 100;
    gHeight = 100;
  };
  void loadinFile(string path);
  double getWidth() { return gWidth; }
  double getHeight() { return gHeight; }
  tuple<double, double, double> getPlayer() { return _player_rec; }
  vector<tuple<double, double, double, double>> getRecs() { return _rec_list; }
  vector<tuple<double, double, double>> getCircles() { return _circ_list; }
  vector<tuple<double, double, double, double>> getRecFake() { return _rec_fake_list; }
  void printTeste();
};

#endif /* READ_H*/
