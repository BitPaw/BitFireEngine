#version 300 es

precision mediump float;

layout(location = 0) out vec4 fragcolor;

struct Material
{
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;
}material;

in struct Vertex 
{
  vec3 Position;
  vec3 Normal;
  vec4 Color;
  vec2 TexturePosition;
} vertex;

uniform sampler2D MaterialTexture;

void main()
{
    // tEST
   //vec3 color = (vec3(vertex.TexturePosition, 1.0f) + vertex.Normal) / 2.0f;

   //fragcolor = vec4(color + vec3(texture(MaterialTexture, vertex.TexturePosition)), 1.0f);

   vec4 textureColor = texture(MaterialTexture, vec2(vertex.TexturePosition.x, -vertex.TexturePosition.y));






   vec3 lightPosition = vec3(1,1,1);
   vec3 lightColor = vec3(1,1,1);
    vec3 ambient = vec3(0.5,0.5,0.5);
         vec3 objectColor = vec3(1,1,1);
   
vec3 norm = normalize(vertex.Normal);
vec3 lightDir = normalize(lightPosition - vertex.Position);  

float diff = max(dot(norm, lightPosition), 0.0);
vec3 diffuse = diff * lightColor;


vec4 diffuseColor =  vec4(((ambient + diffuse) * objectColor), 1.0);









   fragcolor = textureColor * diffuseColor;
}
