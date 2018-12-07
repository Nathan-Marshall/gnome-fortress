// Illumination based on the traditional three-term model

#version 330

// global matrices
uniform mat3 model_mat;

// Attributes passed from the vertex shader
in vec2 position_interp;
in vec2 uv_interp;

// global uniforms

// sprite uniforms
uniform sampler2D main_texture;

void main() 
{
    vec4 color = texture(main_texture, uv_interp);

    // if no alpha, completely cull the pixel
    if (color[3] < 0.01) {
        discard;
    }
    
    gl_FragColor = color;
}