// Illumination based on the traditional three-term model

#version 330

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
uniform vec3 sun_dir = vec3(0, 1, 0);
uniform vec3 sun_color = vec3(1, 0.98, 0.95);

// material uniforms
uniform float ambient_factor = 0;
uniform vec3 diffuse_color = vec3(1, 1, 1);
uniform vec3 specular_color = vec3(0, 0, 0);
uniform float specular_exponent = 100.0;
uniform float alpha = 1.0;

uniform sampler2D diffuse_map;
uniform int diffuse_map_on = 0;
uniform sampler2D gloss_map;
uniform int gloss_map_on = 0;
uniform sampler2D alpha_map;
uniform int alpha_map_on = 0;

uniform samplerCube env_map;
uniform float env_map_factor = 0;

struct BlinnPhongResult {
    float diffuse_intensity;
    float specular_intensity;
};

// returns a vec2 containing the diffuse and specular intensities
BlinnPhongResult calculateBlinnPhong(vec3 light_dir) {
    // Compute Lambertian lighting Id

    vec3 V = normalize(eye_pos - position_interp); // view vector

    vec3 N = normalize(normal_interp); // normal vector
    // reverse the normal if it faces away from the camera, to light each side independently if backface culling is off
    if (dot(V, N) < 0) {
        N = -N;
    }

    vec3 L = normalize(light_dir); // light vector

    float Id = max(dot(N, L), 0.0);
    
    // Compute specular term for Blinn-Phong shading

    vec3 H = normalize(V + L); // halfway vector (between view and light)

    float spec_angle_cos = max(dot(N, H), 0.0);
    float Is = pow(spec_angle_cos, specular_exponent);

    return BlinnPhongResult(Id, Is);
}

vec3 calculateEnvMapColor() {
    vec3 V = normalize(eye_pos - position_interp); // view vector

    vec3 N = normalize(normal_interp); // normal vector
    // reverse the normal if it faces away from the camera, to light each side independently if backface culling is off
    if (dot(V, N) < 0) {
        N = -N;
    }

    float NV = max(dot(N, V), 0.0); // dot product of light and normal
    
    // Compute indirect lighting
    // Reflection vector
    vec3 Lr = 2.0 * NV * N - V;
    // Query environment map
    vec4 il = texture(env_map, Lr);

    return vec3(il);
}

vec3 multiplyColors(vec3 c1, vec3 c2) {
    return vec3(c1[0] * c2[0], c1[1] * c2[1], c1[2] * c2[2]);
}

void main() 
{
    float final_alpha = alpha;
    if (alpha_map_on > 0) {
        final_alpha *= texture(alpha_map, uv_interp).r;
    }
    // if no alpha, completely cull the pixel (right now, we're not using painter's algorithm, so cull with a high threshold)
    if (final_alpha < 0.5) {
        discard;
    }

    vec3 diffuse_color_final = multiplyColors( vec3(texture(diffuse_map, uv_interp)) * diffuse_map_on + vec3(1, 1, 1) * (1 - diffuse_map_on), diffuse_color );
    vec3 ambient_color_final = diffuse_color_final;
    vec3 specular_color_final = multiplyColors( vec3(texture(gloss_map, uv_interp)) * gloss_map_on + vec3(1, 1, 1) * (1 - gloss_map_on), specular_color );

    //BlinnPhongResult blinn_phong_result = calculateBlinnPhong(light_pos - position_interp);
    BlinnPhongResult blinn_phong_result = calculateBlinnPhong(sun_dir);
	vec3 blinn_phong_color = multiplyColors( ambient_factor * ambient_color_final + (1 - ambient_factor) * (blinn_phong_result.diffuse_intensity*diffuse_color_final + blinn_phong_result.specular_intensity*specular_color_final), sun_color );

    vec3 env_map_result = vec3(0, 0, 0);
    if (env_map_factor > 0) {
        env_map_result = calculateEnvMapColor();
    }

    vec3 final_color = blinn_phong_color * (1 - env_map_factor) + env_map_result * env_map_factor;
    
    // Assign light to the fragment
    gl_FragColor = vec4(final_color, final_alpha);
}