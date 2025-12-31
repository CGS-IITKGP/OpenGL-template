#version 430 core

struct Particle {
    vec4 position;
    vec4 velocity;
    float life;
};

layout(std430, binding = 0) buffer Particles {
    Particle p[];
};

void main()
{
    gl_Position = p[gl_VertexID].position;
    gl_PointSize = 3.0;
}