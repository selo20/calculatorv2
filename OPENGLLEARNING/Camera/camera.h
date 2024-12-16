#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cglm/cglm.h>


bool firstMove = 1;


const int W_WIDHT = 800;
const int W_HEIGHT = 600;
float deltaTime = 0.0f;
float lastframe = 0.0f;
float fov = 60.0f;


float unitpersecond = 20.0f;
float sensivity = 100.0f;


float lastx = W_WIDHT/2.0f, lasty = W_HEIGHT/2.0f;

vec3 cameraPos = {0.0f,0.0f,3.0f};
vec3 cameraFront = {0.0f,0.0f,-1.0f};
vec3 cameraSide = {1.0f,0.0f,0.0f};
vec3 cameraUp = {0.0f,1.0f,0.0f};
vec3 cameraFrontal = {0.0f,0.0f,-1.0f};
vec3 cameraPOSFRONT;
float yaw = -90.0f, pitch = 0.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif