#version 330

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

void main()
{
   vec4 hitboxColor = vec4(0.0f, 1.0f, 0.0f, 0.8f);
   vec3 color = vertex.Color.xyz;

   fragcolor = hitboxColor;// + vec4(color, 1.0f);
}