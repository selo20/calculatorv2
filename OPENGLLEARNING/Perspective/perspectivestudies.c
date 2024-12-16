#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cglm/cglm.h>
#include "shader.h"


const int W_WIDHT = 800;
const int W_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
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

    char* vs = "shader.vs";
    char* fs = "shader.fs";

    


    Shader shader = Shader_create(vs,fs);
    Shader_use(&shader);

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    int indicies[] = {
        0,1,3,
        1,2,3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /* glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); */

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);



    
    unsigned int texture[2];
    glGenTextures(2, &texture[0]);

    glBindTexture(GL_TEXTURE_2D,texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);

    

    
    
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,height, 0, GL_RGBA,GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("Failed to load texture2");
    }
    stbi_image_free(data);





    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    //stbi_set_flip_vertically_on_load(true);
    
    data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("Failed to load texture1");
    }
    stbi_image_free(data);






    glUseProgram(shader.ID);

    /* Shader_setInt(&shader,"ourTexture1", 0);
    Shader_setInt(&shader, "ourTexture2", 1); */
    glUniform1i(glGetUniformLocation(shader.ID, "ourTexture1"), 0);
    glUniform1i(glGetUniformLocation(shader.ID, "ourTexture2"), 1);

    /* mat4 ortho;
    glm_ortho(0.0f,(float) W_WIDHT, 0.0f,(float) W_HEIGHT,0.1f,100.0f, ortho); this is for 2d games*/



    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); //gl less or gl greater



    vec3 cubePositions[]= {
    { 0.0f,  0.0f,  0.0f}, 
    {2.0f,  5.0f, -15.0f}, 
    {1.5f, -2.2f, -2.5f},  
    {-3.8f, -2.0f, -12.3f},  
    { 2.4f, -0.4f, -3.5f},  
    {-1.7f,  3.0f, -7.5f},  
    { 1.3f, -2.0f, -2.5f},  
    { 1.5f,  2.0f, -2.5f}, 
    { 1.5f,  0.2f, -1.5f}, 
    {-1.3f,  1.0f, -1.5f}  
    };

    while(!glfwWindowShouldClose(window)){
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture[1]);

        
        unsigned int modelptr, viewptr, projptr;
        //modelptr = glGetUniformLocation(shader.ID,"model");
        viewptr = glGetUniformLocation(shader.ID,"view");
        projptr = glGetUniformLocation(shader.ID,"projection");


        /* mat4 model;
        glm_mat4_identity(model);
        glm_rotate(model, glm_rad((float) glfwGetTime()*100.0f), (vec3) {1.0f,0.9f,0.8f}); */
        /* glm_rotate(model, glm_rad((float) glfwGetTime()*10.0f) ,(vec3) {0.0f, 0.0f,1.0f});
        glm_rotate(model, glm_rad((float) glfwGetTime()*10.0f) ,(vec3) {0.0f, 1.0f,0.0f}); */
        //glm_scale(model, (vec3) {2.0f,2.0f,2.0f});


        mat4 view;
        glm_mat4_identity(view);
        glm_translate(view, (vec3) {0.0f,0.0f, -3.0f});

        mat4 proj;
        glm_perspective(glm_rad(45.0f), (float)W_WIDHT/(float)W_HEIGHT, 0.1f, 100.0f, proj);

        
        
        glUseProgram(shader.ID);
        //glUniformMatrix4fv(modelptr, 1,GL_FALSE, (float*) model);
        glUniformMatrix4fv(viewptr, 1,GL_FALSE, (float*) view);
        glUniformMatrix4fv(projptr, 1,GL_FALSE, (float*) proj);


        glUseProgram(shader.ID);
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++){
            mat4 model;
            glm_mat4_identity(model);
            glm_translate(model,cubePositions[i]);

            float angle = 20.0f * i;
            glm_rotate(model, glm_rad(angle), (vec3) {1.0f, 0.3f, 0.5f});
            if(i%3 == 0){
                glm_rotate(model, glm_rad(angle)+(glm_rad(glfwGetTime())*10.0f), (vec3) {1.0f, 0.3f, 0.5f});
            }
            //glm_translate(model, (vec3){0.0f,-glfwGetTime()/5.0f,0.0f});
            

            modelptr = glGetUniformLocation(shader.ID,"model");
            glUniformMatrix4fv(modelptr,1,GL_FALSE, &model[0][0]);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glDrawArrays(GL_TRIANGLES,0,36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
        
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.ID);

    glfwTerminate();
    return 0;
}