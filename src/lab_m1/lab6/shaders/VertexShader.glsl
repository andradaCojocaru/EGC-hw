#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_position;

void main()
{
    // TODO(student): Send output to fragment shader
     frag_color = v_normal;
     //frag_color = v_color;

     if (sin(Time * 2) < 0)
     {
        frag_color = frag_color + sin(Time * 2);
     }

     frag_normal = v_normal;
     frag_texture = v_texture;
     frag_position = v_position;
    // TODO(student): Compute gl_Position
    //gl_Position = Projection * View * Model * vec4(v_position, 1.0f);
    gl_Position = Projection * View * Model * vec4(v_position[0] * sin(Time * 2), v_position[1] , v_position[2], 1.0f);
}
