#include "tinyxml2.h"
#include <string>
#include <vector>
#include <tuple>

#ifndef READ_H

using namespace std;

class Read{
  double gX;
  double gY;
  double gWidth;
  double gHeight;

  vector<tuple<double,double,double,double>> _rec_list;
  vector<tuple<double,double, double>> _circ_list;
  tuple<double,double, double> _player_rec;

private:
  /* data */
  void _readingRectangle(tinyxml2::XMLElement *element);
  void _readingCircle(tinyxml2::XMLElement *element);

public:
  Read(){
  gX = 0;
  gY = 0;
  gWidth = 100;
  gHeight = 100;

  };
  void loadinFile(string path);
  double getWidth(){return  gWidth;}
  double getHeight(){return gHeight;}
  tuple<double,double, double> getPlayer(){return _player_rec;}
  // ~read_svg();
  vector<tuple<double,double,double,double>> getRecs(){return _rec_list;}
  void printTeste();
};

// read_svg::read_svg(/* args */){}

// read_svg::~read_svg(){}

#endif /* READ_H*/
