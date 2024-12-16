#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 gl_Position;
out vec3 ourColorAsPosition;

void main(){
   ourColorAsPosition = vec3(aPos.x,aPos.y,aPos.z);
   gl_Position = vec4(aPos.x,aPos.y,aPos.z, 1.0);
}