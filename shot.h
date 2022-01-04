#ifndef SHOT_H
#define SHOT_H
#include <GL/gl.h>
#include <GL/glu.h>

#define radiusBullet 5

class Shot {
    GLfloat gx_init;
    GLfloat gy_init;
    GLfloat gX;
    GLfloat gY;
    GLfloat gDirectionAng;
    GLfloat gVel;

  private:
    void drownCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drownShot(GLfloat x, GLfloat y);

  public:
    Shot(GLfloat x, GLfloat y, GLfloat directionAng) {
        gx_init = x;
        gy_init = y;
        gX = x;
        gY = y;
        gDirectionAng = directionAng;
        gVel = 0.1;
    };
    ~Shot();
    void drawn() { drownShot(gX, gY); };
    void move(GLdouble deltaTime);
    bool valid();
    void getPos(GLfloat& xOut, GLfloat& yOut) {
        xOut = gX;
        yOut = gY;
    };
    void getVel(GLfloat& velOut) { velOut = gVel; };
    void getDirectionAng(GLfloat& directionAngOut) {
        directionAngOut = gDirectionAng;
    };
};

#endif /* SHOT_H */
