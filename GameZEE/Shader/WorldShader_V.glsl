#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texturePosition;
//layout(location = 3) in vec4 color;

out struct Vertex 
{
  vec3 Position;
  vec3 Normal;
  vec4 Color;
  vec2 TexturePosition;
} 
vertex;

uniform mat4 MatrixModel;
uniform mat4 MatrixView;
uniform mat4 MatrixProjection;

void main() 
{
    vec4 position4x = vec4(position, 1.0f);
    vec4 matrixModelViewProjection = MatrixProjection * MatrixView * MatrixModel * position4x;

    vertex.Position = vec3(MatrixModel * position4x);
    //vertex.Color = color;
    vertex.Normal = normal; // (model_matrix * vec4(normal, 1.0f)).xyz;
    vertex.TexturePosition = texturePosition; //* tcMultiplier

    gl_Position = matrixModelViewProjection;
}
