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

    char* vs = "shader.vs";
    char* fs = "shader.fs";
    char* lightingfs = "lightingShader.fs";
    char* lightingvs = "lightingShader.vs";

    


    Shader shader = Shader_create(vs,fs);

    Shader lightingShader = Shader_create(lightingvs,lightingfs);

    float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f
};

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);
    


    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);




    

    unsigned int amethistTexture;
    glGenTextures(1, &amethistTexture);

    glBindTexture(GL_TEXTURE_2D, amethistTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("amethist.png", &width, &height, &nrChannels, 0);

    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("Failed to load AmethistBlockTexture");
    }
    stbi_image_free(data);

    Shader_use(&shader);
    glUniform1i(glGetUniformLocation(shader.ID, "amethist"), 0);


    
    data = stbi_load("redstonelamp.png", &width, &height, &nrChannels, 3);
    unsigned int redstonelampTexture;
    glGenTextures(1, &redstonelampTexture);
    glBindTexture(GL_TEXTURE_2D, redstonelampTexture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("Failed to load RedstoneLampkTexture");
    }
    stbi_image_free(data);

    
    Shader_use(&lightingShader);
    glUniform1i(glGetUniformLocation(lightingShader.ID, "redstoneLamp"), 1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); //gl less or gl greater


    vec3 cubePositions[]= {
    {   0.0f,   0.0f,   0.0f},
    {   0.0f,   0.0f,   5.0f},
    };





    vec3 lightColor = {1.0f, 0.1f, 0.5f};
    vec3 lightColor2 = {0.1f, 1.0f, 0.1f};


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

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, redstonelampTexture);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,amethistTexture);
        

        unsigned int modelptr, viewptr, projptr, lightcolorptr, viewPosptr, lightcolorptr2;
        viewptr = glGetUniformLocation(shader.ID,"view");
        projptr = glGetUniformLocation(shader.ID,"projection");
        lightcolorptr = glGetUniformLocation(shader.ID, "lightColor");
        viewPosptr = glGetUniformLocation(shader.ID, "viewPos");
        lightcolorptr2 = glGetUniformLocation(shader.ID, "lightColor2");


        unsigned int modelptrlighting, viewptrlighting, projptrlighting;
        viewptrlighting = glGetUniformLocation(lightingShader.ID,"view");
        projptrlighting = glGetUniformLocation(lightingShader.ID,"projection");

        float angle = glfwGetTime()*10.0f;
        vec3 center;
        center[0] = sin(glm_rad(angle*3.0f))*5.0f;
        center[1] = 0.0f;
        center[2] = cos(glm_rad(angle*3.0f)) *5.0f;

        vec3 center2;
        center2[0] = sin(glm_rad(angle*2.0f))*5.0f;
        center2[1] = cos(glm_rad(angle*2.0f)) *5.0f;
        center2[2] = 0.0f;


        vec3 lightPos;
        vec3 lightPos2;
        glm_vec3_copy(center, lightPos);
        glm_vec3_copy(center2, lightPos2);

        unsigned int lightposptr, lightposptr2;
        lightposptr = glGetUniformLocation(shader.ID, "lightPos");
        lightposptr2 = glGetUniformLocation(shader.ID, "lightPos2");


        mat4 view;
        glm_vec3_add(cameraPos,cameraFront,cameraPOSFRONT);
        glm_lookat(cameraPos,cameraPOSFRONT,cameraUp,view);


        mat4 proj;
        glm_perspective(glm_rad(fov), (float)W_WIDHT/(float)W_HEIGHT, 0.1f, 100.0f, proj);
        
        

        Shader_use(&shader);
        glUniformMatrix4fv(viewptr, 1,GL_FALSE, (float*) view);
        glUniformMatrix4fv(projptr, 1,GL_FALSE, (float*) proj);

        glUniform3fv(lightcolorptr, 1, (float*) lightColor);
        glUniform3fv(lightposptr, 1 , (float*) lightPos);

        glUniform3fv(lightcolorptr2, 1, (float*) lightColor2);
        glUniform3fv(lightposptr2, 1 , (float*) lightPos2);

        glUniform3fv(viewPosptr, 1, (float*) cameraPos);

        Shader_use(&lightingShader);
        glUniformMatrix4fv(viewptrlighting, 1,GL_FALSE, (float*) view);
        glUniformMatrix4fv(projptrlighting, 1,GL_FALSE, (float*) proj);


        Shader_use(&shader);
        glBindVertexArray(VAO);

        
        mat4 model;
        glm_mat4_identity(model);
        glm_rotate(model,glm_rad(angle),(float[3]) {1.0f,0.0f,0.0f});
        glm_rotate(model,glm_rad(angle)*0.8f,(vec3) {0.0f,1.0f,0.0f});
        glm_rotate(model,glm_rad(angle)*0.9f,(vec3) {0.0f,0.0f,1.0f});
        glm_translate(model,cubePositions[0]);
        glm_scale(model, (vec3) {2.0f,2.0f,2.0f});


        modelptr = glGetUniformLocation(shader.ID,"model");
        glUniformMatrix4fv(modelptr,1,GL_FALSE, &model[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        unsigned int lightcolorsptr;
        lightcolorsptr = glGetUniformLocation(lightingShader.ID, "lightcolors");

        Shader_use(&lightingShader);
        glUniform3fv(lightcolorsptr, 1, (float*) lightColor);
        Shader_use(&lightingShader);
        glBindVertexArray(lightVAO);
        
        glm_mat4_identity(model);
        glm_translate(model, center);
        glm_scale(model, (vec3) {0.3f,0.3f,0.3f});
        

        modelptrlighting = glGetUniformLocation(lightingShader.ID, "model");
        glUniformMatrix4fv(modelptrlighting,1,GL_FALSE, &model[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        Shader_use(&lightingShader);
        glUniform3fv(lightcolorsptr, 1, (float*) lightColor2);
        Shader_use(&lightingShader);
        glBindVertexArray(lightVAO);
        
        glm_mat4_identity(model);
        glm_translate(model, center2);
        glm_scale(model, (vec3) {0.3f,0.3f,0.3f});
        

        modelptrlighting = glGetUniformLocation(lightingShader.ID, "model");
        glUniformMatrix4fv(modelptrlighting ,1,GL_FALSE, &model[0][0]);
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