#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#include "./includes/world.h"
#include "./includes/player.h"
#include "./includes/surface.h"
#include "./includes/collision.h"
// #include "./includes/read_svg.h"

#include <iostream>

#define WINDOW_SIZE 800

using namespace std;


World world;
Read readeing;
// Surface* mat_colision[MAX_VIEW_X][MAX_VIEW_Y];
// Collision collision;
// vector<Bot*> bots;

Player* player; 
Shot* shot;

const GLint ViewingWidth =  100;
const GLint ViewingHeight = 100;

int keyStatus[256];


static GLdouble framerate = 0;



void display(void){
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);
   cout << "mundo " << player->getSurface()->getTop() << endl;

   world.draw();
   cout << "fim mundo " << player->getSurface()->getTop() << endl;
   cout << "play " << player->getSurface()->getTop() << endl;
   player->Desenha();



   if (shot){
        Player* bot = world.checkBotsCollision(shot->getPos());
         // shot->draw();
         if(bot != NULL){
            bot->decrementLive();
         }
      }
  
   glEnd();
   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}


void idle(void){
   cout << "idle\n";
   if(player->live() < 0){
      cout << "=========================\n";
      cout << "====== GAME OVER ========\n";
      cout << "=========================\n\n";

   }
   cout << "live\n";

    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    framerate = 1.0 / deltaTime * 1000;
   // cout << "tempos  \t" << "deltaTime: " << deltaTime << "\t prevTime: " << prevTime << "\t framerate: " << framerate << "\t curTime: "<< curTime << "\n"; 
   //  world.setDeltaTime(deltaTime);
    player->moveShot(deltaTime, world.getObstacles());
    if (keyStatus['a'] == 1){
      if(player->getFacing() == 1) player->invertFacing();
      if(world.obstacleCollision(player->getSurface(), "left") == NULL){
        world.moveInX(0.2 * deltaTime);
      //   player->moveSurfaceInX(-0.5 *  deltaTime);
       }
   }
    if(keyStatus['d'] == 1){
      if(player->getFacing() == -1) player->invertFacing();
      if(world.obstacleCollision(player->getSurface(), "right") == NULL){
         world.moveInX(-0.1 * deltaTime);
         // player->moveSurfaceInX(0.5 * deltaTime);
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
   // else{
   //    if(world.hasFloor(player->getSurface()) == NULL){
   //       cout << "gravidadeee\n";
   //       player->moveInY(-0.1 * deltaTime);
   //    }
   // }


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
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f); // Black, no opacity(alpha).

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
   player->moveArm2(y, x);
}

void click(int button, int state, int x, int y){
   printf("Atirou \n");
    shot = player->shootGun();     
}


int main(int argc, char** argv)
{
   // player = new Player(400.0, 400.0, "green");
   //  readeing.loadinFile("/home/jcsbissoli/UFES/2021-2/CG/Trabalho/T1/arena_teste.svg");
   //  readeing.loadinFile("/home/motora/UFES/2021-2/CG/trabalho-CG/arena_teste.svg");
   // tuple<double,double,double> teste = readeing.getPlayer();

   // cout << "Posicao player" << get<0>(teste) << ", " << get<1>(teste) << endl; 
   // readeing.printTeste();

      //  world.build(_test); 
    world.build(); 
    player = world.getPlayer();

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_SIZE, WINDOW_SIZE); 
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Trabalho-CG");
    init ();

   // Receber da função que le o SVG uma matriz d n linha e 4 colunas
   float size_bloc = 10.0;
   float _test[4][4] = {
         {70, 0.0, size_bloc,  2*size_bloc},
         {100, 0.0, size_bloc, 2*size_bloc},
         {200, 0.0, size_bloc,   2*size_bloc},
         {90, 30.0, size_bloc,   2*size_bloc},
         
         };
   



   //  bots = world.getBots();
   //  collision.build(world.getSurfaces());
   //  collision.printMat();

    glutDisplayFunc(display); 
   
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);    
    glutIdleFunc(idle);
    glutPassiveMotionFunc(mira);
    glutMouseFunc(click);


    glutMainLoop();

    return 0;
}
