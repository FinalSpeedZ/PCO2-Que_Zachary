#version 330 core
// Color to be returned
out vec4 FragColor;

// Texture to be passed
uniform sampler2D tex0;

// Color
uniform vec4 color;

// Position of the light source
uniform vec3 lightPos;

// Color of the light: rgb
uniform vec3 lightColor;

// Strength of ambient light
uniform float ambientStr;

// Color of the ambient light
uniform vec3 ambientColor;

// Camera position
uniform vec3 cameraPos;

// Specular strength
uniform float specStr;

// Specular Phong
uniform float specPhong;

// Should recieve the texCoord from the vertex shader
in vec2 texCoord;

// Receive the processed normals from the vertex shader
in vec3 normCoord;

// Receive the position of the vertex to the vertex shader 
in vec3 fragPos;

void main() {



   // If texture exists
   if (all(greaterThan(texture(tex0, texCoord), vec4(0.f)))) 
       FragColor = texture(tex0, texCoord);
   
   // If color exists
   if (any(lessThanEqual(color.xyz, vec3(1.f))))
       FragColor *= color;
}