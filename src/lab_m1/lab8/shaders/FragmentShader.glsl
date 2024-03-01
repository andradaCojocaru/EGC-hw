#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 light_direction2;
uniform vec3 light_position2;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms

uniform vec3 object_color;
uniform int isSpotlight;

// Output
layout(location = 0) out vec4 out_color;


void main()
{   
    vec3 L = normalize( light_position - world_position );
    vec3 L2 = normalize( light_position2 - world_position );

    vec3 V = normalize( eye_position - world_position );

    vec3 H = normalize( L + V );
    vec3 H2 = normalize( L2 + V );

    vec3 R = normalize(reflect(-L, world_normal));
    vec3 R2 = normalize(reflect(-L2, world_normal));
    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!

    float diffuse_light = 0;
    diffuse_light = material_kd * max (dot(world_normal,L), 0);
    float diffuse_light2 = 0;
    diffuse_light2 = material_kd * max (dot(world_normal,L2), 0);

    // TODO(student): Compute specular light component
    float dist = distance (world_position, light_position);
    float dist2 = distance (world_position, light_position2);

    float specular_light = 0;
    float specular_light2 = 0;

    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Gouraud (1971) shading method. There is also the Phong (1975) shading
    // method, which we'll use in the future. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
        //specular_light = material_ks * pow (max (dot (v_normal, H), 0), material_shininess);
    }
    if (diffuse_light2 > 0)
    {
        specular_light2 = material_ks * pow(max(dot(V, R2), 0), material_shininess);
        //specular_light = material_ks * pow (max (dot (v_normal, H), 0), material_shininess);
    }

    // TODO(student): Compute light
    float factor_atenuare = 1 / dist * dist;
	float light	= ambient_light + factor_atenuare * ( diffuse_light + specular_light);
    float light2 = ambient_light + factor_atenuare * ( diffuse_light2 + specular_light2);

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
    if (isSpotlight == 1)
	{
        float cut_off = radians(30);
		float spot_light = dot(-L, light_direction);
		float spot_light_limit= cos(cut_off);
		
		if (spot_light > spot_light_limit)
		{
			float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            float light_att_factor = pow(linear_att, 2);
			light = ambient_light + light_att_factor * (diffuse_light + specular_light);
		} else {
            light = 0;
        }
	} 

	// Write pixel out color
	vec3 colour = object_color * (light + light2);
    //vec3 colour = object_color * light;

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

    // TODO(student): Write pixel out color
    out_color = vec4(colour, 1.0);

}
