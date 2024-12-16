#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform sampler2D amethist;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};
uniform Material material;


struct Light {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform Light light;


void main(){
  vec3 objectColor = texture(amethist, TexCoord).rgb;

  //ambient lighting1
  vec3 ambient = light.ambient * material.ambient;

  //diffuse lighting1
  vec3 norm = normalize(Normal);
  vec3 lightdir = normalize(light.position - FragPos);
  float diff = max(dot(norm, lightdir),0.0);
  vec3 diffuse = light.diffuse * (diff *material.diffuse);

  //specular
  vec3  viewDir = normalize(viewPos - FragPos);
  vec3  reflectDir = reflect(-lightdir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3  specular = light.specular * (spec * material.specular);


  vec3 result = (specular  + diffuse + ambient);
  FragColor = vec4(result , 1.0);
}