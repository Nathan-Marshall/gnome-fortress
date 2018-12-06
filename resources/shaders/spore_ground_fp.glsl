#version 400

// Attributes passed from the geometry shader
in vec4 frag_color;
in vec2 tex_coord;

// Uniform (global) buffer
uniform sampler2D main_texture;


void main (void)
{
    // Get pixel from texture
    vec4 outval = texture(main_texture, tex_coord);
    // Adjust specified object color according to the grayscale texture value
    outval = vec4(outval.r*frag_color.r, outval.g*frag_color.g, outval.b*frag_color.b, sqrt(sqrt(outval.r))*frag_color.a);
    // Set output fragment color
    gl_FragColor = outval;
}
