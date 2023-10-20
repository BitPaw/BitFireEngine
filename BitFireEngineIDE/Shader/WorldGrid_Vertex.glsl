#version 300 es

precision mediump float;

layout(location = 0) in vec3 position;

out struct Vertex 
{
  vec3 Position;
  vec4 Color;
  float DistanceToCamera;
} vertex;

out vec3 ModelScaling;
out mat4 VertexMatrixView;
out mat4 VertexMatrixProjection;


uniform mat4 MatrixModel;
uniform mat4 MatrixView;
uniform mat4 MatrixProjection;


float PXDistanceToCamera(mat4x4 matrixCameraView, mat4x4 matrixModel, vec3 vertexPosition)
{
    vec3 cameraPosition = (inverse(matrixCameraView) * vec4(1.0f,1.0f,1.0f, 1.0f)).xyz;   
    vec3 modelVertexPosition = ( vec4(vertexPosition, 1.0f)).xyz;
    float distanceToCamera = distance(cameraPosition, modelVertexPosition);

   return distanceToCamera * 0000.05f;
   //return 1.0f;
}

vec3 PXScalingGet(mat4x4 matrix)
{
    return vec3(matrix[0][0], matrix[1][1], matrix[2][2]); 
}

void main() 
{
    vec4 matrixModelViewProjection = MatrixProjection * MatrixView * MatrixModel * vec4(position, 1.0f);

    vertex.Position = position;  
    vertex.Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);;
   //vertex.Color = vec4(normalize(vec3(1.0f, 1.0f, 1.0f) + position), 1.0f);
    vertex.DistanceToCamera = 1.0f;//PXDistanceToCamera(MatrixView, MatrixModel, (MatrixProjection * MatrixView * vec4(position, 1.0f)).xyz);

    ModelScaling = PXScalingGet(MatrixModel);
    VertexMatrixView = MatrixView;
    VertexMatrixProjection = MatrixProjection;

    gl_Position = matrixModelViewProjection;
}







/*
layout(set = 0, binding = 0) uniform ViewUniforms {
    mat4 view;
    mat4 proj;
    vec3 pos;
} view;

layout(location = 1) out vec3 nearPoint;
layout(location = 2) out vec3 farPoint;

// Grid position are in clipped space
vec3 gridPlane[6] = vec3[] 
(
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection) 
{
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main() {
    vec3 p = gridPlane[gl_VertexIndex].xyz;
    nearPoint = UnprojectPoint(p.x, p.y, 0.0, view.view, view.proj).xyz; // unprojecting on the near plane
    farPoint = UnprojectPoint(p.x, p.y, 1.0, view.view, view.proj).xyz; // unprojecting on the far plane
    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates
}
*/