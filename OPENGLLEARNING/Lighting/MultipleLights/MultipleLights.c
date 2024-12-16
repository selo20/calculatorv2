#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <cglm/cglm.h>
#define STB_IMAGE_IMPLEMENTATION
#include "shader.h"



bool firstMove = 1;


const int W_WIDHT = 1000;
const int W_HEIGHT = 800;
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

    char* vs = "shader.vert";
    char* fs = "shader.frag";
    char* lightingfs = "lightingShader.frag";
    char* lightingvs = "lightingShader.vert";


    Shader shader = Shader_create(vs,fs);

    Shader lightingShader = Shader_create(lightingvs,lightingfs);

    float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

    vec3 cubePositions[] = {
    { 0.0f,  0.0f,  0.0f},
    { 2.0f,  5.0f, -15.0f},
    {-1.5f, -2.2f, -2.5f},
    {-3.8f, -2.0f, -12.3f},
    { 2.4f, -0.4f, -3.5f},
    {-1.7f,  3.0f, -7.5f},
    { 1.3f, -2.0f, -2.5f},
    { 1.5f,  2.0f, -2.5f},
    { 1.5f,  0.2f, -1.5f},
    {-1.3f,  1.0f, -1.5f}
};

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    


    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);



    unsigned int containerTexture = Shader_setTexture(&shader, "container2.png", "material.diffuse", 0, GL_RGB, GL_RGBA,0 );

    unsigned int redstonelampTexture = Shader_setTexture(&lightingShader, "redstonelamp.png", "redstoneLamp", 1,GL_RGB, GL_RGB, 1);

    unsigned int containerSpecularMap = Shader_setTexture(&shader, "container2_specular.png", "material.specular", 2, GL_RGB, GL_RGBA, 0);

    //unsigned int containerEmissionMap = Shader_setTexture(&shader, "matrix.jpg", "materail.emission", 3, GL_RGB, GL_RGB, 0);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); //gl less or gl greater




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

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,containerTexture);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, redstonelampTexture);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, containerSpecularMap);

        /* glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, containerEmissionMap); */

        vec3 lightColor;
        lightColor[0] = 1.0f; //sin(glfwGetTime() * 2.0f);
        lightColor[1] = 1.0f; //sin(glfwGetTime() * 0.7f);
        lightColor[2] = 1.0f; //sin(glfwGetTime() * 1.3f);        

        float angle = glfwGetTime()*10.0f;
        vec3 center;
        center[0] = sin(glm_rad(angle*3.0f))*5.0f;
        center[1] = 0.0f;
        center[2] = cos(glm_rad(angle*3.0f)) *5.0f;


        vec3 ambientLight;
        vec3 diffuseLight;

        glm_vec3_mul(lightColor, (vec3){0.5f , 0.5f , 0.5f}, diffuseLight);
        glm_vec3_mul(diffuseLight, (vec3){0.2f,0.2f,0.2f}, ambientLight);

        vec3 specularLight = {1.0f,1.0f,1.0f};
        float shininiess = 64.0f;


        vec3 generalLightDirection = {0.0f,-1.0f,0.0f};

        


        vec3 lightPos;
        glm_vec3_copy(center, lightPos);


        mat4 view;
        glm_vec3_add(cameraPos,cameraFront,cameraPOSFRONT);
        glm_lookat(cameraPos,cameraPOSFRONT,cameraUp,view);


        mat4 proj;
        glm_perspective(glm_rad(fov), (float)W_WIDHT/(float)W_HEIGHT, 0.1f, 100.0f, proj);
        
        
        //setting normal shader unifroms
        Shader_use(&shader);

        Shader_setmat4(&shader, "view", view);
        Shader_setmat4(&shader, "projection" , proj);
        Shader_setvec3(&shader, "lightColor", lightColor);
        Shader_setvec3(&shader, "light.position", lightPos);
        Shader_setvec3(&shader, "viewPos", cameraPos);
        Shader_setFloat(&shader, "material.shininess", shininiess);

        Shader_setvec3(&shader, "light.ambient", ambientLight);
        Shader_setvec3(&shader, "light.diffuse", diffuseLight);
        Shader_setvec3(&shader, "light.specular", specularLight);
        Shader_setvec3(&shader, "light.direction", generalLightDirection);

        Shader_setFloat(&shader, "light.constant", 1.0f);
        Shader_setFloat(&shader, "light.linear", 0.09f);
        Shader_setFloat(&shader, "light.quadratic", 0.032f);

        Shader_setvec3(&shader, "light.position", cameraPos);
        Shader_setvec3(&shader, "light.direction", cameraFront);
        Shader_setFloat(&shader, "light.cutOff", cosf(glm_rad(12.5f)));
        Shader_setFloat(&shader, "light.outerCutOff", cosf(glm_rad(17.5f)));
        


        //setting lighting shader unifroms
        Shader_use(&lightingShader);

        Shader_setmat4(&lightingShader, "view", view);
        Shader_setmat4(&lightingShader, "projection", proj);
        



        Shader_use(&shader);
        glBindVertexArray(VAO);

        for(int i = 0; i< size; i++){
            mat4 model;
            glm_mat4_identity(model);

            glm_translate(model,cubePositions[i]);

            glm_rotate(model,glm_rad(angle*i),(float[3]) {1.0f,0.0f,0.0f});
            glm_rotate(model,glm_rad(angle*i)*0.8f,(vec3) {0.0f,1.0f,0.0f});
            glm_rotate(model,glm_rad(angle*i)*0.9f,(vec3) {0.0f,0.0f,1.0f});

            

            Shader_setmat4(&shader, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        


        /* mat4 model;
        glm_mat4_identity(model);
        
        Shader_use(&lightingShader);
        Shader_setvec3(&lightingShader, "lightcolors", lightColor);

        Shader_use(&lightingShader);
        glBindVertexArray(lightVAO);
        
        glm_mat4_identity(model);
        glm_translate(model, center);
        glm_scale(model, (vec3) {0.3f,0.3f,0.3f});
        

        Shader_setmat4(&lightingShader, "model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36); */

        
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