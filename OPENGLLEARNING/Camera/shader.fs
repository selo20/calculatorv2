#version 330 core

//in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D diamondblock;

void main(){
  FragColor = texture(diamondblock, TexCoord);
  //FragColor = texture(ourTexture2, TexCoord);
}
