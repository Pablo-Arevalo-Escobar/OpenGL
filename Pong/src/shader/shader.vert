#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
out vec2 texCoord;
out vec3 color;
flat out int wf;
uniform float offset;
uniform bool wireframe;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;


void main()
{ 
// if(aPos.y < 4)
// {
//	color = vec3(0.0,0.0,1.0);
// }
// else
// {
// 	color = vec3(0.0,1.0,0.0);
// }

 color = vec3(1.0,1.0,1.0);
 vec3 pos= aPos;
 if(wireframe)
 {
	wf = 1;
	vec3 pos = aPos + vec3(10.0,10.0,10.0);
	color = vec3(0.0,0.0,0.0);
 }
 else
 {
	wf = 0;
	vec3 pos = aPos;
 }
 gl_Position = projection*view*model*vec4(pos,1.0);
 texCoord = aTex;
};