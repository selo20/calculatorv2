#version 330 core

//in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main(){
  FragColor = mix(texture(ourTexture2, vec2(TexCoord.x,-TexCoord.y)), texture(ourTexture1, TexCoord),0.8);
  //FragColor = texture(ourTexture2, TexCoord);
}
