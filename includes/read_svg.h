#include "tinyxml2.h"
#include <string>

#ifndef READ_H

using namespace std;


class Read{
private:
    /* data */
  void _readingRectangle(tinyxml2::XMLElement* element);
  void _readingCircle(tinyxml2::XMLElement* element);
public:
    Read(){};
    void loadinFile(string path);
    // ~read_svg();
};

// read_svg::read_svg(/* args */){}

// read_svg::~read_svg(){}

#endif  /* READ_H*/
