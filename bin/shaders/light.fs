#version 330 core

/*
    Basic things
*/
out vec4 FragColor;
in vec2 texture_coords;
in vec3 normals;

/*
    Lighting
*/
#define MAX_LIGHTS 256

uniform vec3 color;

uniform int num_lights;
uniform vec3 light_position[MAX_LIGHTS];
uniform vec3 light_color[MAX_LIGHTS];
uniform float light_size = 0.0;

uniform int fur = 0;

uniform vec3 view_position;
uniform float ambient_light;

uniform float fog_start = 10;
uniform float fog_end = 15;

in vec3 frag_position;

float computeFogFactor()
{
    float distance = length(frag_position - view_position);
    return clamp((distance - fog_start) / (fog_end - fog_start), 0.0, 1.0);
}

vec3 tonemap(vec3 color)
{
    return color / (color + vec3(1.0));
}

/*
    Texture
*/
uniform sampler2D t;

// Calculate our cool ambient lighting
vec3 calculate_ambient();

// Diffuse :3
vec3 calculate_diffuse(int i);

// Specular :0
vec3 calculate_specular(int i);

float calculate_attenuation(int i);

vec3 calculate_diffuse_with_size(int i);

void main()
{
    vec3 ambient = calculate_ambient();

    vec3 total_diffuse = vec3(0.0);
    vec3 total_specular = vec3(0.0);
    
    for(int i = 0; i < num_lights; ++i)
    {
        vec3 to_light = light_position[i] - frag_position;
        float distance = length(to_light);
        vec3 light_dir = normalize(to_light);
        
        float intensity = calculate_attenuation(i);
        
        vec3 norm = normalize(normals);

        vec3 diffuse;
        if(light_size > 0.0)
        {
            diffuse = calculate_diffuse_with_size(i) * intensity;
        }
        else
        {
            float diff = max(dot(norm, light_dir), 0.0);
            diffuse = diff * light_color[i] * intensity;
        }
        
        vec3 view_dir = normalize(view_position - frag_position);
        
        vec3 reflect_dir = reflect(-light_dir, norm);
        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
        vec3 specular = 0.05 * spec * light_color[i] * intensity;
        
        total_diffuse += diffuse * diffuse;
        total_specular += specular * specular;

        vec3 down_light = light_color[i] * 0.6 * intensity;

        total_diffuse += down_light * down_light;
    }
    
    total_diffuse = sqrt(total_diffuse);
    total_specular = sqrt(total_specular);
    
    vec3 total_light = total_diffuse + total_specular;
    
    total_light = min(total_light, vec3(1.0));
    
    vec3 simple_light = ambient + total_light;
    simple_light *= color;
    
    simple_light = simple_light / (simple_light + vec3(1.0));

    if(fur == 1)
    {
        simple_light += vec3(1, 1, 1);
    }

    vec4 texColor = texture(t, texture_coords);

    float grayValue = dot(texColor.rgb, vec3(0.300, 0.580, 0.100));
    vec3 grayColor = vec3(grayValue);

    vec4 finalTexColor = vec4(mix(texColor.rgb, grayColor, (1.0 - ambient_light) * 0.6), texColor.a);

    vec4 baseColor = vec4(color.rgb, 1.0f) * finalTexColor * vec4(simple_light, 1.0);

    vec3 fog_color = vec3(ambient_light);

    float fogFactor = computeFogFactor();
    vec3 finalColor = mix(baseColor.rgb, fog_color, fogFactor);

    FragColor = vec4(finalColor, baseColor.a);

    if(FragColor.a < 0.1)
        discard;
}

// Meow >:3c

vec3 calculate_ambient()
{
    return vec3(ambient_light);
}

vec3 calculate_diffuse(int i)
{
    vec3 norm = normalize(normals);
    vec3 light_dir = normalize(light_position[i] - frag_position);

    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse  = diff * light_color[i];

    return diffuse;
}

vec3 calculate_specular(int i)
{
    float specular_strength = 0.2;
    vec3 norm = normalize(normals);
    vec3 light_dir = normalize(light_position[i] - frag_position);

    vec3 view_dir = normalize(view_position - frag_position);
    vec3 reflect_dir = reflect(-light_dir, norm);

    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 16);
    vec3 specular = specular_strength * spec * light_color[i];

    return specular;
}

float calculate_attenuation(int i)
{
    vec3 to_light = light_position[i] - frag_position;
    float distance = length(to_light);
    
    float adjusted_distance = max(distance - light_size, 0.0);
    
    float attenuation = 1.0 / (1.0 + 0.09 * adjusted_distance + 0.032 * (adjusted_distance * adjusted_distance));
    
    return max(attenuation, 0.0);
}

vec3 calculate_diffuse_with_size(int i)
{
    vec3 norm = normalize(normals);
    vec3 to_light = light_position[i] - frag_position;
    float distance = length(to_light);
    
    if(light_size > 0.0 && distance > 0.0) 
    {
        vec3 light_dir = normalize(to_light);
        
        float NdotL = max(dot(norm, light_dir), 0.0);
        
        float sin_theta = light_size / distance;
        sin_theta = clamp(sin_theta, 0.0, 0.999);
        float theta = asin(sin_theta);
        
        float angle = acos(NdotL);

        float soft_diffuse;
        if(angle <= theta)
        {
            soft_diffuse = 1.0;
        }
        else if(angle < theta + 0.3)
        {
            float t = (angle - theta) / 0.3;
            soft_diffuse = 1.0 - t;
        }
        else
        {
            soft_diffuse = 0.0;
        }
        
        float base_diffuse = NdotL;
        float softness = light_size * 0.5 / max(distance, 0.001);
        softness = clamp(softness, 0.0, 0.8);
        
        float soft_diffuse2 = smoothstep(1.0 - softness, 1.0, base_diffuse);
        
        float final_diffuse = mix(base_diffuse, soft_diffuse2, min(light_size * 0.3, 0.7));
        
        return final_diffuse * light_color[i];
    } 
    else 
    {
        vec3 light_dir = normalize(to_light);
        float diff = max(dot(norm, light_dir), 0.0);
        return diff * light_color[i];
    }
}