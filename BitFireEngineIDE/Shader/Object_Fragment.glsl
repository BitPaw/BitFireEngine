#version 300 es

precision mediump float;

layout(location = 0) out vec4 fragcolor;

struct Material
{
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;
}
material;

in struct Vertex 
{
  vec3 Position;
  vec3 Normal;
  vec4 Color;
  vec2 TexturePosition;
}
vertex;

uniform sampler2D MaterialTexture;

vec4 PXLightCalculate(vec3 lightPosition, vec3 vertexPositon, vec3 normalPosition)
{
    vec3 objectColor = vec3(1,1,1);
    vec3 lightColor = vec3(1,1,1);

    // ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;    
    
     // diffuse 
    vec3 norm = normalize(normalPosition);
    vec3 lightDir = normalize(lightPosition - vertexPositon);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-vertexPositon); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    vec3 specular = specularStrength * spec * lightColor; 
    
    vec3 result = (ambient + diffuse + specular) * objectColor;

    return vec4(result, 1.0f);
}

void main()
{
    vec4 texturedColor = texture(MaterialTexture, vertex.TexturePosition);
    vec4 positionColor = vec4(vertex.TexturePosition, 1.0f, 1.0f);

    vec4 lightColor = PXLightCalculate(vec3(0,500,0), vertex.Position, vertex.Normal);

    fragcolor = texturedColor * lightColor;
    //fragcolor = vertex.Color;
}
