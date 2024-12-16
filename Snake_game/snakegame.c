#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "icon.h"
#include <math.h>
#define TRUE 1
#define FALSE 0

const int WIDTH_S = 800;
const int HEIGHT_S = 800;
const int SQUARE_PIXEL_SIZE = 50;
const int COLUMN_NUMBER = WIDTH_S/SQUARE_PIXEL_SIZE;
const int ROW_NUMBER = HEIGHT_S/SQUARE_PIXEL_SIZE;
const int MARGIN = 2;
const float OPENGLSIZE = 1.0f/COLUMN_NUMBER;
const float RATIO_SQUARE = (float) SQUARE_PIXEL_SIZE/WIDTH_S;
const float RATIO_MARGIN = (float) MARGIN/WIDTH_S;
int NEWLY = FALSE;
int gameover = FALSE;
int MOVED = FALSE;
int AFTER_COLLISION_FRAMES = 0;
const int AREA = ROW_NUMBER*COLUMN_NUMBER;

typedef struct {
    int x,y;
} Position;

typedef struct{
    Position pos[256];
    int lenght;
    int dirY,dirX;
} Snake;

Position food;
Snake snake;

void drawsquare(int x,int y){
    float opengl_position_x = (float)x/COLUMN_NUMBER*2 -1;
    float opengl_position_y = (float)y/ROW_NUMBER*2 -1;
    float opengl_size = (float)2.0f*RATIO_SQUARE;
    float opengl_margin_size = (float)2.0f*RATIO_MARGIN;

    glBegin(GL_QUADS);
    glVertex2f(opengl_position_x+opengl_margin_size,  opengl_position_y+opengl_margin_size);
    glVertex2f(opengl_position_x+opengl_size-opengl_margin_size,  opengl_position_y+opengl_margin_size);
    glVertex2f(opengl_position_x+opengl_size-opengl_margin_size,  opengl_position_y+opengl_size-opengl_margin_size);
    glVertex2f(opengl_position_x+opengl_margin_size,  opengl_position_y+opengl_size-opengl_margin_size);
    glEnd();
}

void drawCircle(int x, int y, float radius, int numSegments) {
    float opengl_position_x = (float)x/COLUMN_NUMBER*2 -1+OPENGLSIZE;
    float opengl_position_y = (float)y/ROW_NUMBER*2 -1+OPENGLSIZE;

    glBegin(GL_LINE_LOOP);  // Use GL_LINE_LOOP to draw a circle
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)numSegments;  // Get the current angle
        float dx = radius * cosf(theta)*(1.0f-RATIO_MARGIN);  // Calculate the x position
        float dy = radius * sinf(theta);  // Calculate the y position
        glVertex2f(opengl_position_x,opengl_position_y);
        glVertex2f(opengl_position_x + dx, opengl_position_y + dy);  // Output vertex
    }
    glEnd();
}


void generatefood(){
    food.x = rand() % COLUMN_NUMBER;
    food.y = rand() % ROW_NUMBER;
    for(int i = 1; i<snake.lenght;i++){
        if(food.x == snake.pos[i].x && food.y == snake.pos[i].y){
            generatefood();
        }
    } 
}



void collisionself(){
    for(int i = 1; i<snake.lenght;i++){
        if(snake.pos[0].x == snake.pos[i].x && snake.pos[0].y == snake.pos[i].y){
            gameover = TRUE;
        }
    }
}

void collisionwall(){
    if(snake.pos[0].x < 0 || snake.pos[0].y < 0 || snake.pos[0].x > COLUMN_NUMBER-1 || snake.pos[0].y > ROW_NUMBER-1){
        gameover = TRUE;
    }
}

void collisionfood(){
    if(snake.pos[0].x == food.x && snake.pos[0].y == food.y){
        snake.lenght++;
        NEWLY = TRUE;
        AFTER_COLLISION_FRAMES = 0;
        generatefood();
    }
}

void drawsnake(){
    glColor3f(0.0f, 0.5f, 0.0f);
    /*if(!AFTER_COLLISION_FRAMES){
        for(int i = 1; i < snake.lenght-1;i++){
            drawsquare(snake.pos[i].x,snake.pos[i].y);
        }
    }
    else{*/
    for(int i = 1; i < snake.lenght-1;i++){
        drawsquare(snake.pos[i].x,snake.pos[i].y);
    
    
    }
}
void drawHead(){
    glColor3f(0.0f, 1.0f, 0.0f);
    drawsquare(snake.pos[0].x,snake.pos[0].y);
}


void movesnake(){

    for(int i = snake.lenght-1 ;i>0;i--){
        snake.pos[i] = snake.pos[i-1];
    }
    snake.pos[0].x += snake.dirX;
    snake.pos[0].y += snake.dirY;

    collisionself();
    collisionwall();
    collisionfood();

}

void drawfood(){
    glColor3f(1.0f, 0.0f, 0.0f);
    float RADIUS = 1.0f*RATIO_SQUARE;
    drawCircle(food.x,food.y,RADIUS,360);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if(!MOVED){
        if(action == GLFW_PRESS){
                switch (key){
                case GLFW_KEY_UP:
                    if(snake.dirY == 0){
                        snake.dirX = 0;
                        snake.dirY = 1;
                        MOVED = TRUE;
                    }
                    break;
                case GLFW_KEY_DOWN:
                    if(snake.dirY == 0){
                        snake.dirX = 0;
                        snake.dirY = -1;
                        MOVED = TRUE;
                    }
                    break;
                case GLFW_KEY_RIGHT:
                    if(snake.dirX == 0){
                        snake.dirX = 1;
                        snake.dirY = 0;
                        MOVED = TRUE;
                    }
                    break;
                case GLFW_KEY_LEFT:
                    if(snake.dirX == 0){
                        snake.dirX = -1;
                        snake.dirY = 0;
                        MOVED = TRUE;
                    }
            }
        }
    }
}


int main(void){
    
    if(!glfwInit()){
        printf("Failed to initialize GLFW\n");
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(WIDTH_S,HEIGHT_S,"Snake game",NULL,NULL);
    if(!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window,key_callback);
    GLFWimage icon;
    icon.width = ICON_WIDTH;
    icon.height = ICON_HEIGHT;
    icon.pixels = (unsigned char *)app_icon;
    glfwSetWindowIcon(window, 1,&icon);

    srand(time(0));
    snake.lenght = 2;
    snake.pos[0].x = 7;
    snake.pos[0].y = 7;
    snake.dirX = 1;
    snake.dirY = 0;
    food.x = 10;
    food.y = 7;

    double lastTime = glfwGetTime();
    double moveDelay = 0.2;

    while (!glfwWindowShouldClose(window)){

        if(!gameover){
            double currentTime = glfwGetTime();

            if(currentTime-lastTime >= moveDelay){
                movesnake();
                MOVED = FALSE;
                lastTime = currentTime;
                AFTER_COLLISION_FRAMES++;
            }
        }


        glClear(GL_COLOR_BUFFER_BIT);

        drawHead();
        drawsnake();
        drawfood();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}