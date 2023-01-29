#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec2 texCoord;
in vec3 color;
flat in int wf;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float alpha;

void main()
{
   vec2 texCoordScaled = vec2(texCoord.s*2.0, texCoord.t*2.0);
   vec4 flippedSmile = texture(tex2,texCoord);
   FragColor = mix(texture(tex1,texCoord), flippedSmile,alpha);
   //FragColor = vec4(color,1.0);



};