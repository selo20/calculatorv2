#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int WIDTH = 800, HEIGHT = 600;
const int GRID_SIZE = 20;
const int COLS = WIDTH / GRID_SIZE;
const int ROWS = HEIGHT / GRID_SIZE;

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position pos[100];  // Max snake length
    int length;
    int dirX, dirY;
} Snake;

Position food;
Snake snake;
int gameOver = 0;

// Function to draw a square for the snake and food
void drawSquare(int x, int y) {
    float xf = (float)x / COLS * 2 - 1;
    float yf = (float)y / ROWS * 2 - 1;
    float size = 2.0f / COLS;

    glBegin(GL_QUADS);
    glVertex2f(xf, yf);
    glVertex2f(xf + size, yf);
    glVertex2f(xf + size, yf + size);
    glVertex2f(xf, yf + size);
    glEnd();
}

// Function to generate food at a random position
void generateFood() {
    food.x = rand() % COLS;
    food.y = rand() % ROWS;
}

// Function to handle snake movement and collisions
void moveSnake() {
    if (gameOver) return;

    // Move body
    for (int i = snake.length - 1; i > 0; i--) {
        snake.pos[i] = snake.pos[i - 1];
    }

    // Move head
    snake.pos[0].x += snake.dirX;
    snake.pos[0].y += snake.dirY;

    // Check collision with wall
    if (snake.pos[0].x < 0 || snake.pos[0].x >= COLS || snake.pos[0].y < 0 || snake.pos[0].y >= ROWS) {
        gameOver = 1;
    }

    // Check collision with self
    for (int i = 1; i < snake.length; i++) {
        if (snake.pos[0].x == snake.pos[i].x && snake.pos[0].y == snake.pos[i].y) {
            gameOver = 1;
        }
    }

    // Check collision with food
    if (snake.pos[0].x == food.x && snake.pos[0].y == food.y) {
        snake.length++;
        generateFood();
    }
}

// Function to draw the snake
void drawSnake() {
    for (int i = 0; i < snake.length; i++) {
        drawSquare(snake.pos[i].x, snake.pos[i].y);
    }
}

// Function to handle keyboard input
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP:
                if (snake.dirY == 0) {
                    snake.dirX = 0;
                    snake.dirY = 1;
                }
                break;
            case GLFW_KEY_DOWN:
                if (snake.dirY == 0) {
                    snake.dirX = 0;
                    snake.dirY = -1;
                }
                break;
            case GLFW_KEY_LEFT:
                if (snake.dirX == 0) {
                    snake.dirX = -1;
                    snake.dirY = 0;
                }
                break;
            case GLFW_KEY_RIGHT:
                if (snake.dirX == 0) {
                    snake.dirX = 1;
                    snake.dirY = 0;
                }
                break;
        }
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // Create a window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Snake Game", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Initialize game state
    srand(time(0));
    snake.length = 1;
    snake.pos[0].x = COLS / 2;
    snake.pos[0].y = ROWS / 2;
    snake.dirX = 1;
    snake.dirY = 0;

    generateFood();

    // Main game loop
    while (!glfwWindowShouldClose(window)) {
        // Move snake
        moveSnake();

        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw snake and food
        drawSnake();
        drawSquare(food.x, food.y);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Simple frame rate control
        glfwWaitEventsTimeout(0.5);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
