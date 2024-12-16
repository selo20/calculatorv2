#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <windows.h>



/* #include "glad.c"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" */


typedef struct
{
    unsigned int ID;
} Shader;

Shader Shader_create(const char* vertexPath, const char* fragmentPath);
void Shader_use(const Shader* shader);
void Shader_setBool(const Shader* shader, const char* name, bool value);
void Shader_setInt(const Shader* shader, const char* name, int value);
void Shader_setFloat(const Shader* shader, const char* name, float value);
void checkCompileErrors(unsigned int shader, const char* type);
void Shader_setvec3(const Shader* shader, const char* name, float vector[3]);
void Shader_setmat4(const Shader* shader, const char* name, float mat4[4][4]);

#endif