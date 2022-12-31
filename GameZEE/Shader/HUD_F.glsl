#version 300 es

precision mediump float;

layout(location = 0) out vec4 fragcolor;

in struct Vertex 
{
  vec3 Position;
  vec4 Color;
  vec2 TexturePosition;
} vertex;

uniform sampler2D MaterialTexture;

void main()
{
    // Vector from fragment to camera (camera always at 0,0,0)
    //vec3 view = normalize(-vertexPosition);
    //vec3 light = normalize(vec3(1.0f, 1.0f, 1.0f));
    //vec3 normal = normalize(vertexNormal);
    //vec3 color = vec3(vertexColor);
    //vec3 reflection = reflect(-light, normal);
   
    //vec3 ambient = color * 0.2;
    //vec3 diffuse = max(dot(normal, light), 0.0) * color;
   // vec3 specular = pow(max(dot(reflection, view), 0.0), 4.0) * color;

   // vec4 calcolr = vec4(ambient + diffuse + specular, 1.0f);

  // vec4 testColor = vec4(1.0f - (vertex.Position.x), 0.5f - (vertex.Position.y), (vertex.Position.x), 0.66f);
   //vec4 testColor = vec4(1.0f-vertex.Position.x, 1.0f, 1.0f, 0.66f);

   vec4 textureColor = texture(MaterialTexture, vertex.TexturePosition);

   if(textureColor.x == 0.0 && textureColor.y == 0.0 && textureColor.z == 0.0)
   {
        discard;
        //  fragcolor = testColor;
   }
   else 
   {
     fragcolor = textureColor;// + testColor;
   }

 

 // fragcolor = vec4( vertexNormal, 1);
}
