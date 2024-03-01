#version 330

// Input
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 point_light_punctiform[100];
uniform int nb_points_punctiform;
uniform vec3 point_light_spot[100];
uniform vec3 color_point_light_punctiform[100];
uniform int nb_points_spot;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    vec4 color1, color2;
    float ambient_light = 0.2;
    vec3 lightTotal = vec3(1, 1, 1) * ambient_light;
    color1 = texture2D(texture_1, texcoord);
    color2 = texture2D(texture_2, texcoord);
    
    vec4 color = mix(color1, color2, 0.5);

    if (color.a < 0.5) {
        discard;
    }
    for (int i = 0; i < nb_points_punctiform; i++) {
        vec3 L = normalize( point_light_punctiform[i] - world_position );
        vec3 V = normalize( eye_position - world_position );
        vec3 H = normalize( L + V );
        vec3 R = normalize(reflect(-L, world_normal));

        vec3 diffuse_light = vec3(0, 0, 0);
        diffuse_light = color_point_light_punctiform[i] * material_kd * max (dot(world_normal,L), 0);

        float dist = distance (world_position, point_light_punctiform[i]);

        vec3 specular_light = vec3(0, 0, 0);

        if (max (dot(world_normal,L), 0) > 0) {
            specular_light = color_point_light_punctiform[i] * material_ks * pow(max(dot(V, R), 0), material_shininess);
            //specular_light = material_ks * pow (max (dot (v_normal, H), 0), material_shininess);
        }

        // TODO(student): Compute light
        float factor_atenuare = 0.5 / dist * dist;
	    vec3 light	= factor_atenuare * ( diffuse_light + specular_light);
        lightTotal += light;
    }

    for (int i = 0; i < nb_points_spot; i++) {
        vec3 L = normalize( point_light_spot[i] - world_position );
        vec3 V = normalize( eye_position - world_position );
        vec3 H = normalize( L + V );
        vec3 R = normalize(reflect(-L, world_normal));
        float cut_off = radians(30);
		float spot_light = dot(-L, light_direction);
		float spot_light_limit= cos(cut_off);
        vec3 light;

        vec3 diffuse_light = vec3(0, 0, 0);
        diffuse_light = vec3(1, 1, 1) * material_kd * max (dot(world_normal,L), 0);

        float dist = distance (world_position, point_light_spot[i]);

        vec3 specular_light = vec3(0, 0, 0);

        if (max (dot(world_normal,L), 0) > 0) {
            specular_light = vec3(1, 1, 1) * material_ks * pow(max(dot(V, R), 0), material_shininess);
            //specular_light = material_ks * pow (max (dot (v_normal, H), 0), material_shininess);
        }
		
		if (spot_light > spot_light_limit) {
			float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            float light_att_factor = pow(linear_att, 2);
			light = light_att_factor * (diffuse_light + specular_light);
		} else {
            light = vec3(0, 0, 0);
        }
        lightTotal += light;
	}

    vec3 L = normalize(-light_direction);
    vec3 V = normalize( eye_position - world_position );
    vec3 H = normalize( L + V );
    vec3 R = normalize(reflect(-L, world_normal));

    vec3 diffuse_light = vec3(0, 0, 0);
    diffuse_light = vec3(1, 1, 1) * material_kd * max (dot(world_normal,L), 0);


    vec3 specular_light = vec3(0, 0, 0);

    if (max (dot(world_normal,L), 0) > 0) {
        specular_light = vec3(1, 1, 1) * material_ks * pow(max(dot(V, R), 0), material_shininess);
        //specular_light = material_ks * pow (max (dot (v_normal, H), 0), material_shininess);
    }

    lightTotal += 0.2 * (diffuse_light + specular_light);
    
    vec4 colour = color * 0.2 + vec4(lightTotal, 0);
    out_color = colour;
}
