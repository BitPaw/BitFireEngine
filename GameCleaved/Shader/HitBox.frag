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

uniform vec4 HitBoxColor;

void main()
{
   vec3 color = vertex.Color.xyz;

   fragcolor = HitBoxColor;// + vec4(color, 1.0f);
}