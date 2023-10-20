#version 300 es

precision mediump float;

layout(location = 0) out vec4 fragcolor;

in struct Vertex 
{
    vec3 Position;
    vec4 Color;
    float DistanceToCamera;
}
vertex;

in vec3 ModelScaling;
in mat4 VertexMatrixView;
in mat4 VertexMatrixProjection;

/*
void main()
{
  
  //  fragcolor = vertex.Color;
   // vec2 coord = fragPos3D.xz * scale;
    //vec2 derivative = fwidth(coord);
    //vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    //float line = min(grid.x, grid.y);
    float minimumz = 0.01;//min(derivative.y, 1);
    float minimumx = 0.01; //min(derivative.x, 1);


    vec4 axisColor = vec4(0,0,0,1);

      if(vertex.Position.x > -0.1 * minimumx && vertex.Position.x < 0.1 * minimumx)
        axisColor.z = 1.0;
    // x axis
    if(vertex.Position.z > -0.1 * minimumz && vertex.Position.z < 0.1 * minimumz)
        axisColor.x = 1.0;



   fragcolor = axisColor;
}

*/

/*

layout(location = 0) in float near; //0.01
layout(location = 1) in float far; //100
layout(location = 2) in vec3 nearPoint;
layout(location = 3) in vec3 farPoint;
layout(location = 4) in mat4 fragView;

layout(location = 8) in mat4 fragProj;

layout(location = 0) out vec4 outColor;
*/

float PXDepthComputeDepth(mat4x4 projectionMatrix, mat4x4 viewMatrix, vec3 currentPosition) 
{
    vec4 clip_space_pos = projectionMatrix * viewMatrix * vec4(currentPosition.xyz, 1.0);
    float depth = clip_space_pos.z / clip_space_pos.w;

    return depth;
}

float PXDepthComputeDepthLinear(mat4x4 projectionMatrix, mat4x4 viewMatrix, vec3 currentPosition, float near, float far) 
{
    float depth = PXDepthComputeDepth(VertexMatrixProjection, VertexMatrixView, currentPosition) * 2.0 - 1.0; // put back between -1 and 1

    float linearDepth = (2.0 * near * far) / (far + near - depth * (far - near)); // get linear value between 0.01 and 100
    return linearDepth / far; // normalize
}

vec4 grid(vec3 currentPosition, float scale) 
{
   float depth = PXDepthComputeDepthLinear(VertexMatrixProjection, VertexMatrixView, currentPosition, 0.0f, 1.0f);

    vec2 coord = currentPosition.xz * scale; // use the scale variable to set the distance between the lines
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1.0f);
    float minimumx = min(derivative.x, 1.0f);
    float cap = 0.001f;

    float loweringFactor = 1.0f;// - min(derivative.x, derivative.y);
    float lineColor = 0.2f;

   // vec4 gridColor = vec4(derivative.x, derivative.y, 0.2f, min(line, 0.6));
   float alpha = (1.0f - min(line, 1.0f)) * loweringFactor;
   vec4 gridColor = vec4(lineColor, lineColor, lineColor, alpha);

    // z axis
    if(currentPosition.x > -cap * minimumx && currentPosition.x < cap * minimumx)
        gridColor.z = 1.0;
    // x axis
    if(currentPosition.z > -cap * minimumz && currentPosition.z < cap * minimumz)
        gridColor.x = 1.0;


    return gridColor;
}

   #define EPSILON 0.0001

void main() 
{
    float distRatio = 1.0f / vertex.DistanceToCamera;
    vec4 gridColor =  grid(vertex.Position, ModelScaling.x);
    vec3 flatColor = normalize(vec3( gridColor.xyz * vertex.Color.xyz));
    float alpha = gridColor.a * vertex.Color.a * distRatio;

    fragcolor = vec4(flatColor, alpha);
}
