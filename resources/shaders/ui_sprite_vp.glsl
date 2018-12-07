#version 130

// Vertex buffer
in vec2 vertex;
in vec2 uv;

// uniforms
uniform mat3 model_mat;

// Attributes forwarded to the fragment shader
out vec2 position_interp;
out vec2 uv_interp;

void main()
{
    // Transform vertex position to screen space
    gl_Position = vec4(model_mat * vec3(vertex, 1), 1);
    position_interp = vec2(model_mat * vec3(vertex, 1));

    uv_interp = uv;
}
