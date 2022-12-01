#version 300 es

precision mediump float;

layout(location = 0) out vec4 fragcolor;

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;
in vec2 vertexTexturePosition;

uniform sampler2D objtexture;

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

   fragcolor = vec4(0,1,0,0.25f);//;texture(objtexture, vertexTexturePosition);

 // fragcolor = vec4( vertexNormal, 1);
}
