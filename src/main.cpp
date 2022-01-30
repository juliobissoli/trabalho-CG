#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#include "../includes/world.h"
#include "../includes/player.h"
#include "../includes/surface.h"
#include "../includes/collision.h"
#include "../includes/read_svg.h"
#include "../includes/polygon.h"
#include <iostream>

#define WINDOW_SIZE 500

using namespace std;


World world;
Read read_svg;
Player* player; 
Shot* shot;
static char str[999];


const GLint ViewingWidth =  500;
const GLint ViewingHeight = 500;

int keyStatus[256];

bool end_game = false;
static GLdouble framerate = 0;



void handleFinish(bool success){  

   //  rectangle(world.getHeight(), world.getWidth(), 0.1, 0.1, 0.1);
    glColor3f(1.0f, 1.0f, 1.0f);  
    glRasterPos2f(player->getX() - 10.0, world.getHeight()/2);
   cout << "ta no fim x = " << player->getX() << " y = "<<  ViewingWidth/2 ;
    if(success)   
        sprintf(str, "VITORIA!");
    else
        sprintf(str, "GAME OVER!");
    char* text;    
    text = str;
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        text++;
    }
    
}
void display(void){
   // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT); 


   
   if(player->live() < 1){
      end_game = true;
      handleFinish(false);
      cout << "=========================\n";
      cout << "====== GAME OVER ========\n";
      cout << "=========================\n\n";
      // return;
   }
   else if(player->success()){
      handleFinish(true);
      cout << "=========================\n";
      cout << "====== Ganhooooooo ======\n";
      cout << "=========================\n\n";
      // return;
   }  
   else {

      world.draw();
      player->draw();


   if (shot){
        Player* bot = world.checkBotsCollision(shot->getPos());
         if(bot != NULL){
            bot->decrementLive();
         }
      }
   }
  
   // glEnd();
   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
   glutPostRedisplay();

}

void resetGame(){
   world.destroi();
   world.build(read_svg.getRecs(),
            read_svg.getCircles(),
            read_svg.getWidth(),
            read_svg.getHeight()
            ); 
    tuple<double, double, double> circ = read_svg.getPlayer();
    player = new Player(get<0>(circ), get<1>(circ),  ((float)get<2>(circ)) * 2.3, "green");
    world.setPlayer(player);
}

void idle(void){
   if(player->live() < 1 ||  player->success()) return;
   else {
    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glLoadIdentity();    
     glOrtho(player->getX() - world.getHeight()/2,
             player->getX() + world.getHeight()/2,
             0.0, 
             world.getHeight(), 
             -1, 1);
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix

    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    framerate = 1.0 / deltaTime * 1000;

    player->moveShot(deltaTime, world.getObstacles());
   
    if (keyStatus['a'] == 1){
      if(player->getFacing() == 1) player->invertFacing();
      if(world.obstacleCollision(player->getSurface(), "left") == NULL){
      //   world.moveInX(0.1 * deltaTime);
        player->moveSurfaceInX(-0.1 *  deltaTime);
        player->moveInX(-0.1 *  deltaTime);
       }
 
   }
    if(keyStatus['d'] == 1){
      if(player->getFacing() == -1) player->invertFacing();
      if(world.obstacleCollision(player->getSurface(), "right") == NULL){
         // world.moveInX(-0.1 * deltaTime);
         player->moveSurfaceInX(0.1 * deltaTime);
         player->moveInX(0.1 * deltaTime);
       }
       if(player->getSurface()->getRight() >= world.getWidth() - 10){
          player->setSuccesPlayer(true);
          cout << "========== GANHOOOO ========\n";
       }
   }
   if (keyStatus['w'] == 1){
        player->moveArm(1);
   }
   if(keyStatus['s'] == 1){
      player->moveArm(-1);
   }
   if(keyStatus['q'] == 1){
      player->decrementLive();
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
       player->handleGravity(deltaTime * 0.5, world.getObstacles());
   }



    glutPostRedisplay();
   }
}


void keyPress(unsigned char key, int x, int y){
   if (key == 'a' || key == 'A'){      
      keyStatus['a'] = 1;      
   } 
   if(key == 'd' || key == 'D' ){
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
   if(key == 'q'){
      keyStatus['q'] = 1;   
   }
   if(key == 'r'){
      cout << "reinicia jogo" << end_game << endl;
      // if(end_game)
       resetGame();        
   }
   if(key == 27){
     exit(0);       
   }
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
   if (argc <= 1){
        cout << "Erro, por favor insira o caminho completo do arquivo" << endl;
        return 0;
    }else{
    string path = argv[argc-1];
    cout << "path " << path;
    read_svg.loadinFile(path);
   //  read_svg.loadinFile("/home/motora/UFES/2021-2/CG/trabalho-CG/arena_teste.svg");
   // read_svg.loadinFile("/home/jcsbissoli/UFES/2021-2/CG/Trabalho/T1/arena_teste.svg");
    world.build(read_svg.getRecs(),
                read_svg.getCircles(),
                read_svg.getWidth(),
                read_svg.getHeight()
                ); 
    }
    tuple<double, double, double> circ = read_svg.getPlayer();
    player = new Player(get<0>(circ), get<1>(circ),  ((float)get<2>(circ)) * 2.3, "green");
    world.setPlayer(player);

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_SIZE, WINDOW_SIZE); 
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Trabalho-CG");
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);    
    glutIdleFunc(idle);
    glutPassiveMotionFunc(mira);
    glutMouseFunc(click);

    init ();

    glutMainLoop();

    return 0;
}
