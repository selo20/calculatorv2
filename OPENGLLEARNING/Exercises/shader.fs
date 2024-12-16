#version 330 core

in vec3 ourColorAsPosition;
out vec4 FragColor;

void main(){
  
  FragColor = vec4(ourColorAsPosition, 1.0);
}