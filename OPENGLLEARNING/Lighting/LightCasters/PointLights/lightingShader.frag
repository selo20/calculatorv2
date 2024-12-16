#version 330 core

out vec4 FragColor;

uniform sampler2D redstoneLamp;
uniform vec3 lightcolors;
in vec2 TexCoord;

void main(){
  FragColor = texture(redstoneLamp, TexCoord) * vec4(lightcolors,1.0);
}
