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
uniform vec3 sun_dir = vec3(0, 1f, 1f);
uniform sampler2D diffuse_map;

// Material attributes (constants)
float ambient_intensity = 0.1f;
float phong_exponent = 100.0;

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
    float Is = pow(spec_angle_cos, phong_exponent);

    return BlinnPhongResult(Id, Is);
}

void main() 
{
    vec3 ambient_color = vec3(texture(diffuse_map, uv_interp)) * ambient_intensity;
    vec3 diffuse_color = vec3(texture(diffuse_map, uv_interp));
    vec3 specular_color = vec3(1, 1, 1);

    //BlinnPhongResult blinn_phong = calculateBlinnPhong(light_pos - position_interp);
    BlinnPhongResult blinn_phong = calculateBlinnPhong(sun_dir);
	vec4 final_color = vec4(ambient_color + blinn_phong.diffuse_intensity*diffuse_color + blinn_phong.specular_intensity*specular_color, 1);
    
    // Assign light to the fragment
    gl_FragColor = final_color;
}