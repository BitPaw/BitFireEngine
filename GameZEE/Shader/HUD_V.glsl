#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texturePosition;
//layout(location = 2) in vec4 color;

out struct Vertex 
{
  vec3 Position;
  vec4 Color;
  vec2 TexturePosition;
} vertex;

uniform mat4 MatrixModel;

void main() 
{
    vec4 matrixPosition = MatrixModel * vec4(position, 1);

    //vertexColor = color;
    //vertexNormal = normal;
    vertex.Position = position;
    vertex.Color = vec4(position, 1.0);
    vertex.TexturePosition = texturePosition;
    //vertexTexturePosition = texturePosition;

    gl_Position = matrixPosition;
}
