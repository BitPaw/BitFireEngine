#version 300 es

precision highp float;
precision mediump int;

layout(location = 0) in vec3 position;

out vec3 TexturePosition;

uniform mat4 MatrixView;
uniform mat4 MatrixProjection;

void main() 
 {
    vec4 pos = MatrixProjection *  MatrixView * vec4(position, 1.0);
   
    TexturePosition = position;

    gl_Position = pos;//.xyww;
}
