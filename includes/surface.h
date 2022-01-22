#ifndef SURFACE_H
#define SURFACE_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>
#include <tuple>

#include "polygon.h"

using namespace std;


class Surface {

    GLfloat _x;
    GLfloat _y;

    GLfloat _ySize;
    GLfloat _xSize;
    tuple<float, float, float> _color;


    private:
      void drowSurface();
      void desenhaRef(int position);


    public:
      Surface(GLfloat x, GLfloat y, GLfloat x_size, GLfloat y_size){
        _x = x;
        _y = y; 
        _ySize = y_size ;
        _xSize = x_size ;
        _color = {0.0, 0.0, 0.0};

      }

     void draw() {
         drowSurface();
        //  desenhaRef(-1);
        //  desenhaRef(0);
        //  desenhaRef(1);
        //  desenhaRef(2);
        //  desenhaRef(4);
     };
    void resetX(GLfloat dx){_x = dx;};
    void resetY(GLfloat dy){_y = dy;};

    void traslateX(GLfloat dx){_x += dx;};
    
    float getTop(){return  _y + _ySize;}
    float getBooton(){return  _y;}
    float getLeft(){return _x - (_xSize / 2);}
    float getRight(){return _x + (_xSize / 2);}
    float getYCenter(){return _y + (_ySize / 2);}
    float getXCenter(){return _x;}
    void changeColor(){_color = {0.0, 1.0, 0.5};}

    bool isInternal(GLfloat x, GLfloat y);

    float getWidth(){return _xSize;}


};

#endif /*SURFACE_H*/