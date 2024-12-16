#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cglm/cglm.h>
#include "shader.h"



bool firstMove = 1;


const int W_WIDHT = 800;
const int W_HEIGHT = 600;
float deltaTime = 0.0f;
float lastframe = 0.0f;
float fov = 60.0f;


float unitpersecond = 7.5f;
float sensivity = 150.0f;


float lastx = W_WIDHT/2.0f, lasty = W_HEIGHT/2.0f;

vec3 cameraPos = {0.0f,0.0f,3.0f};
vec3 cameraFront = {0.0f,0.0f,-1.0f};
vec3 cameraSide = {1.0f,0.0f,0.0f};
vec3 cameraUp = {0.0f,1.0f,0.0f};
vec3 cameraFrontal = {0.0f,0.0f,-1.0f};
vec3 cameraPOSFRONT;
float yaw = -90.0f, pitch = 0.0f;






void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 60.0f)
        fov = 60.0f;
}



void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(firstMove){
        lastx = xpos;
        lasty = ypos;
        firstMove = 0;
    }
    
    float offsetx = xpos - lastx;
    float offsety = lasty - ypos;
    lastx = xpos;
    lasty = ypos;

    float deltasens = sensivity * deltaTime;
    offsetx *= deltasens;
    offsety *= deltasens;

    yaw += offsetx;
    pitch += offsety;

    if(pitch >= 89.9f)
        pitch = 89.9f;
    if(pitch <= -89.9f)
        pitch = -89.9f;

    vec3 direction, frontalDirection;

    direction[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    direction[1] = sin(glm_rad(pitch));
    direction[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));

    frontalDirection[0] = cos(glm_rad(yaw));
    frontalDirection[1] = 0.0f;
    frontalDirection[2] = sin(glm_rad(yaw));

    glm_normalize(direction);
    glm_vec3_copy(direction, cameraFront);

    glm_normalize(frontalDirection);
    glm_vec3_copy(frontalDirection, cameraFrontal);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }

    float cameraSpeed = deltaTime*unitpersecond;
    vec3 camfontmultip;
    mat4 sidewaysmultip;

    vec3 frontal;

    glm_mat4_identity(sidewaysmultip);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        glm_vec3_scale(cameraFrontal,cameraSpeed,camfontmultip);
        glm_vec3_add(cameraPos,camfontmultip,cameraPos);
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        glm_vec3_scale(cameraFrontal,cameraSpeed,camfontmultip);
        glm_vec3_sub(cameraPos,camfontmultip,cameraPos);
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        glm_cross(cameraFront,cameraUp,cameraSide);
        glm_normalize(cameraSide);
        glm_vec3_scale(cameraSide,cameraSpeed,camfontmultip);
        glm_vec3_add(cameraPos,camfontmultip,cameraPos);
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        glm_cross(cameraFront,cameraUp,cameraSide);
        glm_normalize(cameraSide);
        glm_vec3_scale(cameraSide,cameraSpeed,camfontmultip);
        glm_vec3_sub(cameraPos,camfontmultip,cameraPos);
    }
    if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        glm_vec3_scale(cameraUp,cameraSpeed,camfontmultip);
        glm_vec3_sub(cameraPos,camfontmultip,cameraPos);
    }
    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
        glm_vec3_scale(cameraUp,cameraSpeed,camfontmultip);
        glm_vec3_add(cameraPos,camfontmultip,cameraPos);
    }
}


int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(W_WIDHT,W_HEIGHT,"Hello Window",NULL,NULL);

    if(window==NULL){
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
    printf("Failed to initialize GLAD");
    return -1;
    }
    glViewport(0,0,W_WIDHT,W_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    char* vs = "shader.vs";
    char* fs = "shader.fs";
    char* lighting = "lightingShader.fs";

    


    Shader shader = Shader_create(vs,fs);

    Shader lightingShader = Shader_create(vs,lighting);

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);




    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); //gl less or gl greater


    vec3 cubePositions[]= {
    {   0.0f,   0.0f,   0.0f},
    {   5.0f,   0.0f,   3.0f}
    };



    vec3 lightColor = {1.0f, 1.0f, 1.0f};
    vec3 objectColor = {1.0f, 0.5f, 0.31f};


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    int size = sizeof(cubePositions)/sizeof(float)/3;
    unsigned int fps = 0;
    float second1 = 0.0f;

    while(!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastframe;
        lastframe = currentFrame;

        //for fps
        fps+= 1;
        if(currentFrame-second1 >= 1.0f){
            second1 = glfwGetTime();
            printf("%d\n",fps);
            fps = 0;
        }


        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        unsigned int modelptr, viewptr, projptr, objectcolorptr, lightcolorptr;
        viewptr = glGetUniformLocation(shader.ID,"view");
        projptr = glGetUniformLocation(shader.ID,"projection");
        objectcolorptr = glGetUniformLocation(shader.ID, "objectColor");
        lightcolorptr = glGetUniformLocation(shader.ID, "lightColor");

        unsigned int modelptrlighting, viewptrlighting, projptrlighting;
        viewptrlighting = glGetUniformLocation(lightingShader.ID,"view");
        projptrlighting = glGetUniformLocation(lightingShader.ID,"projection");


        mat4 view;
        glm_vec3_add(cameraPos,cameraFront,cameraPOSFRONT);
        glm_lookat(cameraPos,cameraPOSFRONT,cameraUp,view);


        mat4 proj;
        glm_perspective(glm_rad(fov), (float)W_WIDHT/(float)W_HEIGHT, 0.1f, 100.0f, proj);


        Shader_use(&shader);
        glUniformMatrix4fv(viewptr, 1,GL_FALSE, (float*) view);
        glUniformMatrix4fv(projptr, 1,GL_FALSE, (float*) proj);
        glUniform3fv(lightcolorptr, 1, (float*) lightColor);
        glUniform3fv(objectcolorptr, 1, (float*) objectColor);

        Shader_use(&lightingShader);
        glUniformMatrix4fv(viewptrlighting, 1,GL_FALSE, (float*) view);
        glUniformMatrix4fv(projptrlighting, 1,GL_FALSE, (float*) proj);


        Shader_use(&shader);
        glBindVertexArray(VAO);

        mat4 model;
        glm_mat4_identity(model);
        glm_translate(model,cubePositions[0]);

        modelptr = glGetUniformLocation(shader.ID,"model");
        glUniformMatrix4fv(modelptr,1,GL_FALSE, &model[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);



        Shader_use(&lightingShader);
        glBindVertexArray(lightVAO);
        glm_mat4_identity(model);
        glm_translate(model, cubePositions[1]);
        
        modelptrlighting = glGetUniformLocation(lightingShader.ID, "model");
        glUniformMatrix4fv(modelptrlighting,1,GL_FALSE, &model[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);



        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
        
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &lightVAO);
    glDeleteProgram(shader.ID);
    glDeleteProgram(lightingShader.ID);

    glfwTerminate();
    return 0;
}