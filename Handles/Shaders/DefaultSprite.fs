#version 330 core

out vec4 color;

in VS_OUT
{
	vec2 uv;
	vec4 color;
} fs_in;

struct Material
{
	sampler2D texture_diffuse;
	sampler2D texture_specular;
	sampler2D texture_reflection;
	sampler2D texture_normal;
	float shininess;
};

uniform Material material;

void main() 
{
	vec4 textureColor = texture(material.texture_diffuse, fs_in.uv);
    color = fs_in.color * textureColor;
}