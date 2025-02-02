#version 450 core

layout(location=0)in vec3 vPos;
layout(location =1)in vec3 vColor;

uniform mat4 camMatrix;
uniform mat4 Modle;

out vec3 Color;
out float Height;
void main(){
	gl_Position = camMatrix* Modle* vec4(vPos,1.0);
	Height = clamp(vPos.y,0.2,1.0);
	Color = vColor;
};
