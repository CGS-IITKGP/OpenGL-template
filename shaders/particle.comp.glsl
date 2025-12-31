#version 430 core
layout(local_size_x = 256) in;

struct Particle {
    vec4 position;
    vec4 velocity;
    float life;
};

layout(std430, binding = 0) buffer Particles {
    Particle p[];
};

uniform float dt;

void main()
{
    uint id = gl_GlobalInvocationID.x;
    if (id >= p.length()) return;

    p[id].position.xyz += p[id].velocity.xyz * dt;
    p[id].life -= dt;

    // Respawn
    if (p[id].life <= 0.0) {
        p[id].position = vec4(0, 0, 0, 1);
        p[id].life = 1.0;
    }
}