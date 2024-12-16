#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 lightColor2;
uniform vec3 lightPos2;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform sampler2D amethist;


void main(){
  vec3 objectColor = vec3(texture(amethist, TexCoord));

  //ambient lighting1
  float ambientstrengt = 0.05;
  vec3 ambient = ambientstrengt * lightColor;

  //ambient lighting2
  vec3 ambient2 = ambientstrengt * lightColor2;


  //diffuse lighting1
  vec3 norm = normalize(Normal);
  vec3 lightdir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightdir),0.0);
  vec3 diffuse = diff * lightColor;

  //diffuse lighting2
  norm = normalize(Normal);
  vec3 lightdir2 = normalize(lightPos2 - FragPos);
  diff = max(dot(norm, lightdir2),0.0);
  vec3 diffuse2 = diff * lightColor2;


  //specular
  float specularStrength = 0.25;
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightdir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
  vec3 specular = specularStrength * spec * lightColor;

  //specular
  vec3 reflectDir2 = reflect(-lightdir2, norm);
  float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), 128);
  vec3 specular2 = specularStrength * spec2 * lightColor2;


  vec3 result = (specular + specular2 + diffuse + diffuse2 + ambient + ambient2) * objectColor;
  FragColor = vec4( result , 1.0);
}
