#version 130

// Vertex buffer
in vec2 vertex;

// uniforms
uniform mat3 model_mat;
uniform vec2 uv_min;
uniform vec2 uv_max;

// Attributes forwarded to the fragment shader
out vec2 position_interp;
out vec2 uv_interp;

void main()
{
    // Transform vertex position to screen space
    gl_Position = vec4(model_mat * vec3(vertex, 1), 1);
    position_interp = vec2(model_mat * vec3(vertex, 1));
    uv_interp = uv_min + (uv_max - uv_min) * (vec2(0.5, 0.5) + vertex * 0.5);
}
