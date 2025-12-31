#version 410 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

// Must match VS output exactly
in vec4 Color[];
out vec4 bColor;

uniform float uTime;

// Emit one triangle
void emitTriangle(vec4 a, vec4 b, vec4 c, vec4 ca, vec4 cb, vec4 cc)
{
    bColor = ca;
    gl_Position = a;
    EmitVertex();

    bColor = cb;
    gl_Position = b;
    EmitVertex();

    bColor = cc;
    gl_Position = c;
    EmitVertex();

    EndPrimitive();
}

void main()
{
    // Original positions
    vec4 v0 = gl_in[0].gl_Position;
    vec4 v1 = gl_in[1].gl_Position;
    vec4 v2 = gl_in[2].gl_Position;

    // Original colors
    vec4 c0 = Color[0];
    vec4 c1 = Color[1];
    vec4 c2 = Color[2];

    // Midpoints
    vec4 m01 = (v0 + v1) * 0.5;
    vec4 m12 = (v1 + v2) * 0.5;
    vec4 m20 = (v2 + v0) * 0.5;

    // Midpoints colors
    vec4 c01 = (c0 + c1) * 0.5;
    vec4 c12 = (c1 + c2) * 0.5;
    vec4 c20 = (c2 + c0) * 0.5;

    // Triangle center
    vec4 center = (v0 + v1 + v2) / 3.0;

    // Animation strength
    float strength = abs(sin(uTime)) * 0.2;

    // Directions
    vec4 d0 = normalize(v0 - center) * strength;
    vec4 d1 = normalize(v1 - center) * strength;
    vec4 d2 = normalize(v2 - center) * strength;

    // Emit 4 triangles
    // 3 corner triangles: move outward
    emitTriangle(v0 + d0, m01 + d0, m20 + d0, c0, c01, c20);
    emitTriangle(v1 + d1, m12 + d1, m01 + d1, c1, c12, c01);
    emitTriangle(v2 + d2, m20 + d2, m12 + d2, c2, c20, c12);

    // Center triangle: stays fixed
    emitTriangle(m01, m12, m20, c01, c12, c20);
}