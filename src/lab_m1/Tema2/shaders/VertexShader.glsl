#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 PosCar;
uniform vec3 Color;

// Output
out vec3 color;

void main()
{
     color = Color;
     vec4 PosV = Model * vec4(v_position, 1.0f);
     float scaleFactor = 0.02f;
     float dist = distance (vec4(PosCar, 1.0f), PosV);

     PosV.y = PosV.y - dist * dist * scaleFactor;

     //gl_Position = Projection * View * Model * vec4(v_position, 1.0f);
     gl_Position = Projection * View * PosV;

}
