#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform float timeSeconds;
uniform int orangeDef;
uniform float Time;
uniform int blueDef;
uniform int whiteDef;
uniform int greenDef;
uniform int yellowDef;
uniform int redDef;

// output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main()
{
	// send output to fragment shader
	frag_position	= v_position ;
	frag_normal	= v_normal;
	frag_texture	= v_texture;
	frag_color	= object_color;

	// compute gl_Position
	if (orangeDef == 1) {
		frag_position.x = cos(timeSeconds * v_position.x) * 0.25f;
		frag_position.y = cos(timeSeconds * v_position.y) * 0.25f;
		frag_position.z = sin(timeSeconds * v_position.z * 5) * 0.25f;
		
	}
	if (blueDef == 1 || yellowDef == 1 || greenDef == 1 || whiteDef == 1 || redDef == 1) {
		frag_position.x = cos(Time * v_position.x) * 0.25f;
		frag_position.y = cos(Time * v_position.y) * 0.25f;
		frag_position.z = sin(Time * v_position.z * 5) * 0.25f;
	}
	
	gl_Position = Projection * View * Model * vec4(frag_position, 1);
}
