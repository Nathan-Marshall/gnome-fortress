#version 130

// Vertex buffer
in vec3 vertex;
in vec3 normal;
in vec3 color;
in vec2 uv;

// global matrices
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;
uniform mat4 normal_mat;
uniform vec3 eye_pos;

// Attributes forwarded to the fragment shader
out vec3 position_interp;
out vec3 normal_interp;
out vec4 color_interp;
out vec2 uv_interp;

void main()
{
    // Transform vertex position to screen space
    gl_Position = projection_mat * view_mat * world_mat * vec4(vertex, 1);

    // Transform vertex position to world space
    position_interp = vec3(world_mat * vec4(vertex, 1));

    // Transform normal directions to world space
    normal_interp = vec3(normal_mat * vec4(normal, 0));

    color_interp = vec4(color, 1);

    uv_interp = uv;
}
