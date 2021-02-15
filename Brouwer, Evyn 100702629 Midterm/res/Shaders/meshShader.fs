#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct pointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct dirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 uv;

uniform vec3 viewPos;
uniform Material material;
uniform pointLight light;
uniform dirLight dLight;

uniform vec3 ambientToggle;
uniform vec3 diffuseToggle;
uniform vec3 specularToggle;

void main()
{
    //pointLight
   //ambient
   vec3 ambient = light.ambient * vec3(texture(material.diffuse, uv)) * 0.3;
   
   //diffuse
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(light.position - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, uv));
   
   //specular
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);  
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = light.specular * spec * vec3(texture(material.specular, uv));
   
   //emission 
   vec3 emission = vec3(texture(material.emission, uv));
   
   float distance = length(light.position-FragPos);
   float attenuation = 1.0/(light.constant + light.linear*distance + light.quadratic * (distance * distance));

   ambient  *= attenuation; 
   diffuse  *= attenuation;
   specular *= attenuation; 


   vec3 lightResult = vec3(0.0,0.0,0.0);

        lightResult = lightResult + (ambient * ambientToggle);
        lightResult = lightResult + (diffuse * diffuseToggle);
        lightResult = lightResult + (specular * specularToggle);


     //vec3 lightResult =(ambient + diffuse + specular + emission);//original
   vec4 result = vec4(lightResult,1.0);
   FragColor = result;



   //directional Light
   ///ambient
   //vec3 ambient = dLight.ambient * vec3(texture(material.diffuse, uv)) * 0.1;
   //
   ////diffuse
   //vec3 norm = normalize(Normal);
   //vec3 lightDir = normalize(-dLight.direction);
   //float diff = max(dot(norm, lightDir), 0.0);
   //vec3 diffuse = dLight.diffuse * diff * vec3(texture(material.diffuse, uv));
   //
   ////specular
   //vec3 viewDir = normalize(viewPos - FragPos);
   //vec3 reflectDir = reflect(-lightDir, norm);  
   //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   //vec3 specular = dLight.specular * spec * vec3(texture(material.specular, uv));
   //
   ////emission 
   //vec3 emission = vec3(texture(material.emission, uv));
   //
   //vec3 lightResult = (ambient + diffuse + specular + emission);
   //vec4 result = vec4(lightResult,1.0);
   //FragColor = result;
}

