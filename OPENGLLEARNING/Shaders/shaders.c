#include "shaders.h"


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