#version 300 es

layout(location = 0) in vec2 InputVertexTexturePosition;
//layout(location = 1) in vec3 InputVertexNormal;
layout(location = 1) in vec3 InputVertexPosition;

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
    vec4 position4x = vec4(InputVertexPosition, 1.0f);
    vec4 matrixModelViewProjection = MatrixProjection * MatrixView * MatrixModel * position4x;

    //vertex.Position = vec3(MatrixModel * vec4(normal, 1.0f));
    vertex.Position = vec3(MatrixModel * position4x);
    vertex.Normal = vec3(0,0,0);//InputVertexNormal;
    vertex.TexturePosition = vec2(-InputVertexTexturePosition.x, InputVertexTexturePosition.y); //* tcMultiplier
    //vertex.Color = position4x;

    vertex.Color = vec4(vertex.TexturePosition, 1.0f, 1.0f);
   // vertex.Normal = vec3(0.0f,0.0f,0.0f); // (model_matrix * vec4(normal, 1.0f)).xyz;


    gl_Position = matrixModelViewProjection;
}
