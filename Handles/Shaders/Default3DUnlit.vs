#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in mat4 toWorldMat;

out VS_OUT
{
	vec2 uv;
} vs_out;

flat out int instanceID;

uniform mat4 projection;
uniform mat4 view;

void main() 
{
    //transform the world space coordinates from the spritebatch to clip coordinates with the ortho projection matrix
    gl_Position = projection * view * toWorldMat * vec4(position, 1.0);
	
    vs_out.uv = uv;
	
	instanceID = gl_InstanceID;
}