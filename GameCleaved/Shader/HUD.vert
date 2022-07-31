#version 300 es

layout(location = 0) in vec3 position;

out vec2 TexturePosition;
out vec3 TextureScaling;

uniform mat4 MatrixModel;
uniform mat4 MatrixView;

void main() 
 {
    vec4 position4x = vec4(position, 1.0f);
    vec4 matrixModelViewProjection = MatrixModel * position4x;

    TexturePosition = position.xy;
    TextureScaling = vec3(MatrixModel[0][0],MatrixModel[1][1],MatrixModel[2][2]);

    gl_Position = matrixModelViewProjection;
}
