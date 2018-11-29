#version 400

// Vertex buffer
in vec3 vertex;
in vec3 normal;
in vec3 color;

// Uniform (global) buffer
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 normal_mat;
uniform float timer;
uniform float power = 1.0;

// Attributes forwarded to the geometry shader
out vec4 particle_color;
out float particle_id;

// Simulation parameters (constants)
float accel = 1.2; // An acceleration applied to the particles coming from some attraction force
float speed = 1.0; // Control the speed of the motion
float duration = 1.3;

// Define some useful constants
const float pi = 3.1415926536;
const float pi_over_two = 1.5707963268;
const float two_pi = 2.0*pi;


const vec3 color0 = vec3(0.03, 0.03, 0.8);
const vec3 color1 = vec3(0.8, 0.4, 0.03);
const float color1Circtime = 0.7f;
const vec3 color2 = vec3(0.1, 0.1, 0.1);
const float color2Circtime = 0.86f;

vec3 getColor(float circtime) {
    if (circtime < color1Circtime) {
        float p = circtime / color1Circtime;
        return color0 * (1-p) + color1 * p;
    } else if (circtime < color2Circtime) {
        float p = (circtime - color1Circtime) / (color2Circtime - color1Circtime);
        return color1 * (1-p) + color2 * p;
    } else {
        return color2;
    }
}

void main()
{
    // Define particle id
    particle_id = color.r; // Derived from the particle color. We use the id to keep track of particles

    // define time in a cyclic manner
    float t = (timer + particle_id * duration) - duration * floor((timer + particle_id * duration) / duration);
    // normalized time with respect to total duration
    float circtime = t / duration;
                                    
    // Set up parameters of the particle motion

    // First, work in local model coordinates (do not apply any transformation)
    vec3 position = vertex;
    position += speed*normal*accel*power*t*t; // Particle moves up
    
    // Define output position but do not apply the projection matrix yet
    gl_Position = view_mat * world_mat * vec4(position, 1.0);
    
    // Define amount of blending depending on the cyclic time
    float alpha = (1.0 - circtime*circtime) * power;
    particle_color = vec4(getColor(circtime), alpha*0.2);
}