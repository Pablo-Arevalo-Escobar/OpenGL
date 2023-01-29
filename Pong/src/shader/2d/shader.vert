#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 color;

uniform mat4 model;
uniform mat4 projection;
uniform vec3 pixel_color;



void main()
{ 
	color = pixel_color;
	gl_Position = projection*model*vec4(aPos,1.0);
};