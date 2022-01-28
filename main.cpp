#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#include "./includes/world.h"
#include "./includes/player.h"
#include "./includes/surface.h"
#include "./includes/collision.h"
#include "./includes/read_svg.h"

#include <iostream>

#define WINDOW_SIZE 800

using namespace std;


World world;
Read reade_svg;
Player* player; 
Shot* shot;
static char str[999];


const GLint ViewingWidth =  500;
const GLint ViewingHeight = 500;

int keyStatus[256];


static GLdouble framerate = 0;



void handleFinish(bool success){  
    glColor3f(1.0f, 1.0f, 1.0f); 
    tuple<GLfloat, GLfloat> coord = player->getPos(); 
    glRasterPos2f(get<0>(coord) + 30.0, 0);
    if(success)
        sprintf(str, "VITORIA!");
    else
        sprintf(str, "GAME OVER!");
    char* text;    
    text = str;
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *text);
        text++;
    }
    
}
void display(void){
   glClear (GL_COLOR_BUFFER_BIT);
   if(player->live() < 0){
      handleFinish(false);
      cout << "=========================\n";
      cout << "====== GAME OVER ========\n";
      cout << "=========================\n\n";

   }
   world.draw();
   player->draw();
   if (shot){
        Player* bot = world.checkBotsCollision(shot->getPos());
         if(bot != NULL){
            bot->decrementLive();
         }
      }
  
   glEnd();
   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}



void idle(void){
   
   if(player->live() < 0)return;
   
    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glLoadIdentity();
    
    glOrtho(player->getX() - world.getHeight()/2,
            player->getX() + world.getHeight()/2,
            -world.getHeight()/2, world.getHeight()/2,
            -1,1);    
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix

    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    framerate = 1.0 / deltaTime * 1000;
   // cout << "tempos  \t" << "deltaTime: " << deltaTime << "\t prevTime: " << prevTime << "\t framerate: " << framerate << "\t curTime: "<< curTime << "\n"; 

    player->moveShot(deltaTime, world.getObstacles());
   
    if (keyStatus['a'] == 1){
      if(player->getFacing() == 1) player->invertFacing();
      if(world.obstacleCollision(player->getSurface(), "left") == NULL){
        world.moveInX(0.1 * deltaTime);
      //   player->moveSurfaceInX(-0.1 *  deltaTime);
       }
   }
    if(keyStatus['d'] == 1){
      if(player->getFacing() == -1) player->invertFacing();
      if(world.obstacleCollision(player->getSurface(), "right") == NULL){
         world.moveInX(-0.1 * deltaTime);
         // player->moveSurfaceInX(0.1 * deltaTime);
       }
   }
    if (keyStatus['w'] == 1){
        player->moveArm(1);
   }
    if(keyStatus['s'] == 1){
      player->moveArm(-1);
   }
   if(keyStatus[' '] ==  1){
      if(!player->hasJumping()){   
       player->jump(deltaTime, world.getObstacles());      
      }

   }
   if(player->hasJumping()){
      player->jump(deltaTime, world.getObstacles());  
   }
   // // se não esta pulando aplica gravidade;
   else{
       player->handleGravity(deltaTime, world.getObstacles());
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
     shot = player->shootGun();      
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black, no opacity(alpha).

    glMatrixMode(GL_PROJECTION);  // Select the projection matrix
    glOrtho(-(ViewingWidth / 2),  // X coordinate of left edge
            (ViewingWidth / 2),   // X coordinate of right edge
            -(ViewingHeight / 2), // Y coordinate of bottom edge
            (ViewingHeight / 2),  // Y coordinate of top edge
            -100,                 // Z coordinate of the “near” plane
            100);                 // Z coordinate of the “far” plane
    
   // glMatrixMode(GL_PROJECTION);  
   // glOrtho(0.0, ViewingWidth, 0.0, ViewingWidth, -ViewingWidth, ViewingWidth);


    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
}

void mira(int x, int y){
   y = WINDOW_SIZE  - y;
   player->moveArm2(y, x);
}

void click(int button, int state, int x, int y){
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    framerate = 1.0 / deltaTime * 1000;

    if(button == GLUT_RIGHT_BUTTON){
        if(state == GLUT_DOWN && !player->hasJumping()){ 
                player->jump(deltaTime, world.getObstacles());      
         }          
        }
    if (button == GLUT_LEFT_BUTTON && state != GLUT_DOWN){
         printf("Atirou \n");
         shot = player->shootGun();  
    }
}


int main(int argc, char** argv)
{
   //  readeing.loadinFile("/home/jcsbissoli/UFES/2021-2/CG/Trabalho/T1/arena_teste.svg");
   //  readeing.loadinFile("/home/motora/UFES/2021-2/CG/trabalho-CG/arena_teste.svg");
   reade_svg.loadinFile("/home/jcsbissoli/UFES/2021-2/CG/Trabalho/T1/arena_teste.svg");
    world.build(reade_svg.getRecs(),
                reade_svg.getCircles(),
                reade_svg.getWidth(),
                reade_svg.getHeight()
                ); 
    tuple<double, double, double> circ = reade_svg.getPlayer();
    player = new Player(get<0>(circ), get<1>(circ),  ((float)get<2>(circ)) * 2.3, "green");
    world.setPlayer(player);

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_SIZE, WINDOW_SIZE); 
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Trabalho-CG");
    init ();
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);    
    glutIdleFunc(idle);
    glutPassiveMotionFunc(mira);
    glutMouseFunc(click);


    glutMainLoop();

    return 0;
}
