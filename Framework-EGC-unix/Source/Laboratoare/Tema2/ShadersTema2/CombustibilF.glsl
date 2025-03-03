#version 330

// get values from fragment shader
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
in vec3 frag_color;

layout(location = 0) out vec4 out_color;

void main()
{
	// write pixel out color
	out_color	= vec4(frag_color, 1.f);
}
