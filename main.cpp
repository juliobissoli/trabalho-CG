#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#include "./includes/world.h"
#include "./includes/player.h"
#include "./includes/surface.h"

#include <iostream>

#define WINDOW_SIZE 500

using namespace std;


World world;
Player player;  
Shot* shot;

const GLint ViewingWidth =  WINDOW_SIZE;
const GLint ViewingHeight = WINDOW_SIZE;

int keyStatus[256];


static GLdouble framerate = 0;

int detectCollision(Surface* s1, Surface* s2){
      // printf("x %d \t y %d \n", s1->getRight() == s2->getLeft(), s1->getBooton() > s2->getTop());
      //  return s1->getRight() >= s2->getLeft() || s1->getBooton() > s2->getTop();
      printf("esq(s1) >= dir(s2)= %d \t  dir(s1) <= esq(s2)= %d \n", s1->getLeft() >= s2->getRight() , s1->getRight() <= s2->getLeft());
      return   s1->getLeft() >=  s2->getRight()
            && s1->getRight() <= s2->getLeft()
            // || s2->getTop() <= s1->getBooton()
            ;
}

// Superficie ques esta se movendo (s1) colide de "frente" (direita)
// com a "traseira" (direita) de s2
int frontalCollision(Surface* s1, Surface* s2){
 return s1->getRight() >= s2->getLeft() &&
        s1->getRight() <= s2->getRight();
}

int rearCollision(Surface* s1, Surface* s2){
 return s1->getLeft() <= s2->getRight() &&
        s1->getLeft() >= s2->getLeft();
}

int above(Surface* s1, Surface* s2){
    return s1->getBooton() > s2->getTop();
}

int below(Surface* s1, Surface* s2){
   printf("booton %f \t top %f \n ",s1->getBooton(), s2->getTop());
   return s1->getBooton() <= s2->getTop();
}


void display(void){
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);
   
   world.draw();
   player.Desenha();
   

   if (shot){
         shot->draw();
      }
  
   glEnd();
   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}


void idle(void){

    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    framerate = 1.0 / deltaTime * 1000;
    if (keyStatus['a'] == 1){
       if(!rearCollision(player.getSurface(), world.getSurface()) ||
          above(player.getSurface(), world.getSurface())){
        world.moveInX(0.5 * deltaTime);
      //   player.moveInX(-0.5 * 0.3 * deltaTime);
       }
   }
    if(keyStatus['d'] == 1){
      //  if(player.getRigth() < world.getLeft() || player.getBooton() > world.getTop()){
      if(!frontalCollision(player.getSurface(), world.getSurface()) ||
          above(player.getSurface(), world.getSurface())){
         world.moveInX(-0.5 * deltaTime);
         // player.moveInX(0.5 * 0.3 * deltaTime);
       }
   }
    if (keyStatus['w'] == 1){
        player.moveArm(1);
   }
    if(keyStatus['s'] == 1){
      player.moveArm(-1);
   }
   if(keyStatus[' '] ==  1){
     player.jump(deltaTime);      

   }

   if(player.hasJumping()){
      player.jump(deltaTime);  
      if(
         
         below(player.getSurface(), world.getSurface())
         && rearCollision(player.getSurface(), world.getSurface())
         && frontalCollision(player.getSurface(), world.getSurface())
      )
       player.stopJump();
   }

   if(shot){
       shot->move(deltaTime);    
    if (!shot->valid()) {
            delete shot;
            shot = NULL;
        }
   }

    glutPostRedisplay();
}


void keyPress(unsigned char key, int x, int y){
   if (key == 'a'){      
      keyStatus['a'] = 1;      
   } 
   if(key == 'd'){
      keyStatus['d'] = 1;      
   } 
    // So para teste
    if (key == 'w'){      
      keyStatus['w'] = 1;      
   } 
   if(key == 's'){
      keyStatus['s'] = 1;      
   } 
   if(key == 't'){
     shot = player.shootGun();      
   } 
   if(key == ' '){
      keyStatus[' '] = 1;   
   }
//    if(key == 'w'){
//       keyStatus['w'] = 1;      
//    }
   glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
    // ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
}


void init(void) {
   //  ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black, no opacity(alpha).

   //  glMatrixMode(GL_PROJECTION);  // Select the projection matrix
   //  glOrtho(-(ViewingWidth / 2),  // X coordinate of left edge
   //          (ViewingWidth / 2),   // X coordinate of right edge
   //          -(ViewingHeight / 2), // Y coordinate of bottom edge
   //          (ViewingHeight / 2),  // Y coordinate of top edge
   //          -100,                 // Z coordinate of the “near” plane
   //          100);                 // Z coordinate of the “far” plane
    
   glMatrixMode(GL_PROJECTION);  
    glOrtho(0.0, ViewingWidth, 0.0, ViewingWidth, -ViewingWidth, ViewingWidth);


    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
}

void mira(int x, int y){
   y = WINDOW_SIZE  - y;
   player.moveArm2(y, x);
}

void click(int button, int state, int x, int y){
   printf("Atirou \n");
    shot = player.shootGun();     
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_SIZE, WINDOW_SIZE); 
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Trabalho-CG");
    init ();

   
   // Receber da função que le o SVG uma matris d n linha e 4 colunas
   float _test[2][4] = {{50 *2, 50.0, size_bloc*0.5, size_bloc}, {300, 100, size_bloc*2, size_bloc}};

    world.build(_test); 

    glutDisplayFunc(display); 
   
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);    
    glutIdleFunc(idle);
    glutPassiveMotionFunc(mira);
    glutMouseFunc(click);


    glutMainLoop();

    return 0;
}
