// Illumination based on the traditional three-term model

#version 140

// global matrices
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;
uniform mat4 normal_mat;
uniform vec3 eye_pos;

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 color_interp;
in vec2 uv_interp;

// global uniforms
uniform vec3 sun_dir = vec3(0, 1, 1);
uniform vec3 sun_color = vec3(1, 0.98, 0.95);

uniform vec3 diffuse_color = vec3(1, 1, 1);
uniform vec3 specular_color = vec3(0, 0, 0);
uniform float specular_exponent = 100.0;

uniform sampler2D diffuse_map;
uniform int diffuse_map_on = 0;
uniform sampler2D gloss_map;
uniform int gloss_map_on = 0;

// Material attributes (constants)
float ambient_intensity = 0.1;

struct BlinnPhongResult {
    float diffuse_intensity;
    float specular_intensity;
};

// returns a vec2 containing the diffuse and specular intensities
BlinnPhongResult calculateBlinnPhong(vec3 light_dir) {
    // Compute Lambertian lighting Id

    vec3 N = normalize(normal_interp); // normal vector

    vec3 L = normalize(light_dir); // light vector

    float Id = max(dot(N, L), 0.0);
    
    // Compute specular term for Blinn-Phong shading

    vec3 V = normalize(eye_pos - position_interp); // view vector

    vec3 H = normalize(V + L); // halfway vector (between view and light)

    float spec_angle_cos = max(dot(N, H), 0.0);
    float Is = pow(spec_angle_cos, specular_exponent);

    return BlinnPhongResult(Id, Is);
}

vec3 multiplyColors(vec3 c1, vec3 c2) {
    return vec3(c1[0] * c2[0], c1[1] * c2[1], c1[2] * c2[2]);
}

void main() 
{
    vec3 diffuse_color_final = multiplyColors( vec3(texture(diffuse_map, uv_interp)) * diffuse_map_on + vec3(1, 1, 1) * (1 - diffuse_map_on), diffuse_color );
    vec3 ambient_color_final = diffuse_color_final * ambient_intensity;
    vec3 specular_color_final = multiplyColors( vec3(texture(gloss_map, uv_interp)) * gloss_map_on + vec3(1, 1, 1) * (1 - gloss_map_on), specular_color );

    //BlinnPhongResult blinn_phong_result = calculateBlinnPhong(light_pos - position_interp);
    BlinnPhongResult blinn_phong_result = calculateBlinnPhong(sun_dir);
	vec4 blinn_phong_color = vec4(multiplyColors( ambient_color_final + blinn_phong_result.diffuse_intensity*diffuse_color_final + blinn_phong_result.specular_intensity*specular_color_final, sun_color ), 1);
    
    // Assign light to the fragment
    gl_FragColor = blinn_phong_color;
}