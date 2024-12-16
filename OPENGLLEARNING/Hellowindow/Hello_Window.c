#include <glad/glad.h>
#include "glad.c"
#include <GLFW/glfw3.h>
#include <stdio.h>



//output of the shader is gl_position
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


//fragment color is (r,g,b,opequeness)
const char *fragmentShadeSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";









//resizing of the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}









void processInput(GLFWwindow *window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
}








int main(){

    //zorunlu init fonksiyonlari
    glfwInit();
    //versiyonunu belirtiyoruz major,minor --> 3,3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //bunu anlamadim
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //birada glfw objesi tanimliyoruz window isminde 
    GLFWwindow* window = glfwCreateWindow(800,600,"Hello Window",NULL,NULL);

    //window dogru calisiyor mu diye bir kontrol
    if(window==NULL){
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }


    //gorunen seyi window yaptik
    glfwMakeContextCurrent(window);




    //glad icin gerekli
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
    printf("Failed to initialize GLAD");
    return -1;
    }
    
    //ekranin sol alt kosesi 0,0 kordinati olsun demek ve ekranin boyutlarini girmek lazim
    glViewport(0,0,800,600);

    //glfw fonksiyonlarini tanimlayabiliyoruz kendimiz ve burada da ekrani resize eden komudu tanimliyoruz
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);








    //defining a shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //shader sourcesini ayarliyoruz
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //checking if the compliling worked ok
    int  success;
    char infoLog[512];
    //gets the object and check if it is ok then updates the value of succes
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    //if the succes equal to 0 
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); //takes the infolog and puts it to infolog we defined
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
        for(int i = 0; i<512;i++){
            printf("%c",infoLog[i]);
        }
    }







    //defining fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShadeSource, NULL);
    glCompileShader(fragmentShader);
    

    //checking if the compiling worked
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        for(int i = 0; i<512;i++){
            printf("%c",infoLog[i]);
        }
    }







    //creating a program with our shaders binded to it
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    //first we attach both shaders to program
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    //then we link the shader program to the program
    glLinkProgram(shaderProgram);

    //checking if shaders linked properly and working properly
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        for(int i = 0; i<512;i++){
            printf("%c",infoLog[i]);
        }
    }
    glUseProgram(shaderProgram);

    //once we linked the written codes to program we no longer need the actual objects so we delete them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* this is triangle
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
        0.5f, -0.5f, 0.0f, // right 
        0.0f,  0.5f, 0.0f  // top 
    };*/

    //this is two triangles adding up to a rectangle
    //these are all the unique cordinates
    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };

    //this will draw a triangle using the 1th 2nd and 4th cordinates and then 1th 2nd 3rd 
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };







    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);







    //alt+f4 ya da kapatma tusuna basildiginda glfwwindowshouldclose true donuyor 
    while(!glfwWindowShouldClose(window)){
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);
        /*eski frame kaydedilirken yeni frame cizilyor ama yeni frame cizilirken aninda cizilmedigi icin kotu bir goruntu olusabiliyo
        bunun onune gecmek icin en son cizimi bitmis olan frame ekranda dururken arka planda yeni frame ciziliyor*/
        
        //render bolgesi
        //render bolgesi
        //render bolgesi


        glUseProgram(shaderProgram);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        


        //render bolgesi bitis
        //render bolgesi bitis
        //render bolgesi bitis

        glfwSwapBuffers(window);
        //bu input olarak bir seyin yapilip yapilmadigini kontrol edip window objesini guncelliyor
        glfwPollEvents();

    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);



    glfwTerminate();
    return 0;
}