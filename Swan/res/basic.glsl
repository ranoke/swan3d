#type vertex
#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;

uniform mat4 u_ProjView;
uniform mat4 u_Model;

out vec4 vertexColor; // specify a color output to the fragment shader

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
  gl_Position = u_ProjView*u_Model*vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
  vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color

  TexCoord = aUv;
}

#type fragment
#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
  FragColor = texture(ourTexture, TexCoord);
} 
