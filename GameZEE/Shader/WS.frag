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
   vec3 color = (vec3(vertex.TexturePosition, 1.0f) + vertex.Normal) / 2.0f;

   fragcolor = vec4(color + vec3(texture(MaterialTexture, vertex.TexturePosition)), 1.0f);
}
