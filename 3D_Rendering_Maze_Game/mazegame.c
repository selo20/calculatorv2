#include <GLFW/glfw3.h>
#include <stdio.h>

void drawCube(float x, float y, float z, float size){


    glBegin(GL_QUADS);
    //color front face
    glColor3d(255,0,0);
    //front face
    glVertex3f(x,y,z);
    glVertex3f(x+size,y,z);
    glVertex3f(x+size,y+size,z);
    glVertex3f(x,y+size,z);



    //parameters for right face
    float rightx = x+size;
    float righty = y;
    float rightz = z;
    //color right face
    glColor3d(0,255,0);
    //right face
    glVertex3f(rightx,righty,rightz);
    glVertex3f(rightx,righty,rightz+size);
    glVertex3f(rightx,righty+size,rightz+size);
    glVertex3f(rightx,righty+size,rightz);



    //parameter for up face
    float upx = x;
    float upy = y+size;
    float upz = z;
    //color of up face
    glColor3d(0,0,255);
    //up face
    glVertex3f(upx,upy,upz);
    glVertex3f(upx+size,upy,upz);
    glVertex3f(upx+size,upy,upz+size);
    glVertex3f(upx,upy,upz+size);
    glEnd();




}



















void initGLFW() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return;
    }

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "3D Maze Game", NULL, NULL);
    if (!window) {
        glfwTerminate();
        printf("Failed to create window\n");
        return;
    }

    glfwMakeContextCurrent(window);
    
    // Game loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Render scene here


        drawCube(-0.5f,0.0f,0.0f,0.25f);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

int main() {
    initGLFW();
    return 0;
}
