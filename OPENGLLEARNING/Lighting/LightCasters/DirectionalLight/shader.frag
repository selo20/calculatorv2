#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 viewPos;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  //sampler2D emission;
  float shininess;
};
uniform Material material;


struct Light {
  //vec3 position; no longer needed when using directional lighting
  vec3 direction; //instead we use direction

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform Light light;


void main(){
  //ambient lighting1
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

  //diffuse lighting1
  vec3 norm = normalize(Normal);
  vec3 lightdir = normalize(-light.direction);
  float diff = max(dot(norm, lightdir),0.0);
  vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse,TexCoord)));

  //specular
  vec3  viewDir = normalize(viewPos - FragPos);
  vec3  reflectDir = reflect(-lightdir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3  specular = light.specular * (spec * texture(material.specular, TexCoord).rgb);

  //emssion
  //vec3 emission = texture(material.emission, TexCoord).rgb;


  vec3 result = specular  + diffuse + ambient;// + emission;
  FragColor = vec4(result , 1.0);
}