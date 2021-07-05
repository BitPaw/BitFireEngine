#version 300 es

precision mediump float;

layout(location = 0) out vec4 fragcolor;

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
    vec3 color = vec3(vertex.Color);
    vec3 reflection = reflect(-light, normal);
   
    vec3 ambient = color * 0.2;
    vec3 diffuse = max(dot(normal, light), 0.0) * color;
    vec3 specular = pow(max(dot(reflection, view), 0.0), 4.0) * color;

    vec4 calcolr = vec4((ambient + diffuse + specular) *vertex.Normal, 1.0f);

	//fragcolor = calcolr;
   fragcolor = texture(objtexture, vertex.TexturePosition) * calcolr;

  //fragcolor = vec4( normal, 1);
}