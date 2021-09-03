#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 texturePosition;

out struct Vertex 
{
  vec3 Position;
  vec3 Normal;
  vec4 Color;
  vec2 TexturePosition;
} vertex;

uniform mat4 ModelView;
uniform mat4 InverseModelView;
uniform mat4 ModelViewProjection;

void main() 
{
    vertex.Position = vec3(ModelView) * position;
    vertex.Color = color;
    vertex.Normal = mat3(InverseModelView) * normal;
    vertex.TexturePosition = texturePosition;

    gl_Position = (ModelViewProjection * vec4(position, 1.0f));
}