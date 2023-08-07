#version 300 es

precision mediump float;

layout(location = 0) out vec4 fragcolor;

struct Material
{
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;
}
material;

in struct Vertex 
{
  vec3 Position;
  vec3 Normal;
  vec4 Color;
  vec2 TexturePosition;
}
vertex;

uniform sampler2D MaterialTexture;

void main()
{
    float red = 1.0f;//vertex.Color.r / 1000.0f;
    float green =  1.0f;//vertex.Color.g / 1000.0f;
    float blue =  1.0f;//vertex.Color.b / 1000.0f;

    fragcolor = vec4(red, green, blue, 1.0f);// + texture(MaterialTexture, vertex.TexturePosition);
}
