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

uniform sampler2D objtexture;

void main()
{
    // Vector from fragment to camera (camera always at 0,0,0)
    vec3 view = normalize(vertex.Position);
    vec3 light = normalize(vec3(1.0f, 1.0f, 1.0f));
    vec3 normal = normalize(vertex.Normal);
    vec3 reflection = reflect(-light, normal);
   
    material.Ambient = vertex.Color * 0.2;
    material.Diffuse = max(dot(normal, light), 0.0) * vertex.Color;
    material.Specular = pow(max(dot(reflection, view), 0.0), 4.0) * vertex.Color;

    vec4 calcolr = material.Ambient + material.Diffuse + material.Specular;

   fragcolor = texture(objtexture, vertex.TexturePosition) * vec4(calcolr.xyz, 1.0f);
}