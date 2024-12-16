#include "shader.h"

char* readShaderFile(const char* filepath){
    FILE* file = fopen(filepath,"rb");
    if(!file){
        fprintf(stderr,"ERROR::SHADER::FILE_NOT_FOUND %s",filepath);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long lenght = ftell(file);
    fseek(file,0,SEEK_SET);

    char* buffer = (char*)malloc(lenght+1);
    if(buffer){
        fread(buffer,1,lenght,file);
        buffer[lenght] = '\0';
    }
    fclose(file);
    return buffer;
}

Shader Shader_create(const char* vertexPath, const char* fragmentPath){
    Shader shader;
    shader.ID = 0;

    char *vertexCode = readShaderFile(vertexPath);
    char *fragmentCode = readShaderFile(fragmentPath);


    if(!vertexCode||!fragmentCode){
        free(vertexCode);
        free(fragmentCode);
        return shader;
    }

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1, (const char**) &vertexCode,NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex,"VERTEX");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,(const char**)&fragmentCode,NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment,"FRAGMENT");

    shader.ID = glCreateProgram();
    glAttachShader(shader.ID,vertex);
    glAttachShader(shader.ID,fragment);
    glLinkProgram(shader.ID);
    checkCompileErrors(shader.ID,"PROGRAM");

    glUseProgram(shader.ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader;
}


int glfwInitwithwindow(const int height,const int widht,const char* name){

}

void Shader_use(const Shader* shader){
    glUseProgram(shader->ID);
}

void Shader_setBool(const Shader* shader, const char* name, bool value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), (int)value);
}

void Shader_setInt(const Shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

void Shader_setFloat(const Shader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

void Shader_setvec3(const Shader* shader, const char* name, float vector[3]){
    glUniform3fv(glGetUniformLocation(shader->ID, name) , 1 , (const float*) vector);
}

void Shader_setmat4(const Shader* shader, const char* name, float mat4[4][4]){
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, name), 1 , GL_FALSE, (const float*)mat4);
}


unsigned int Shader_setTexture(const Shader* shader, const char* texturePath, const char* uniformName, const int textureLocation, int RGBtypestore, int RGBtypedata, int unpackalignment){
    unsigned int Texture;
    glGenTextures(1, &Texture);

    glBindTexture(GL_TEXTURE_2D, Texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, unpackalignment);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, RGBtypestore, width,height, 0, RGBtypedata, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("Failed to load %s", uniformName);
    }
    stbi_image_free(data);

    Shader_use(shader);
    glUniform1i(glGetUniformLocation(shader->ID, uniformName), textureLocation);

    return Texture;
}






void checkCompileErrors(unsigned int shader, const char* type) {
    int success;
    char infoLog[1024];

    if (strcmp(type, "PROGRAM") != 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
}