#include "./player.h" 
#include <string>
#include <cmath>


void Player::drownBody(GLint height, GLint width) {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-width/2, 0);
        glVertex2f(width/2, 0);
        glVertex2f(width/2, height);
        glVertex2f(-width/2, height);
    // clang-format on
    glEnd();
}

void Player::drownPlayer(GLint x, GLint y){
    glPushMatrix();
    glTranslatef(x, y, 0);
    Player::drownBody(body_height, body_width);
    glPopMatrix();

}

void Player::moveInX(GLfloat dx){ 
    int unit = MOVE_UNIT;
    gX += (dx * unit);
}


Shot* Player::shootGun() {
    printf("Angulo ==> \n");
    int radius = 10;
    // int totalAngle = gTheta1 + gTheta2 + gTheta3;
    int totalAngle = 30;
    int firstX = gX + radius * sin(-totalAngle * M_PI / 180);
    int firstY = gY + (body_height / 2) + radius * cos(-totalAngle * M_PI / 180);
    // int secondX = firstX + (radius)*sin(-(gTheta1 + gTheta2) * M_PI / 180);
    // int secondY = firstY + (radius)*cos(-(gTheta1 + gTheta2) * M_PI / 180);
    // int thirdX = secondX + radius * sin(-totalAngle * M_PI / 180);
    // int thirdY = secondY + radius * cos(-totalAngle * M_PI / 180);

    // return new Shot(thirdX, thirdY, totalAngle);
    return new Shot(firstX, firstY, totalAngle);
}