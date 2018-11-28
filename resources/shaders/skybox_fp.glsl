#version 130

// Attributes passed from the vertex shader
in vec3 uvw_interp;
uniform samplerCube cube_map;
 
void main()
{    
    gl_FragColor = texture(cube_map, uvw_interp);
}
