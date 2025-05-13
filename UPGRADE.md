# Upgrade OpenGL from 4.1 to 4.6

**Shaders**: Change `#version 410 core` to `#version 460 core` in these files
- [shader.frag.glsl](./shaders/shader.frag.glsl)
- [shader.vert.glsl](./shaders/shader.vert.glsl)
- [triangle.frag.glsl](./shaders/triangle.frag.glsl)
- [triangle.vert.glsl](./shaders/triangle.vert.glsl)
<br />

[**main.cpp**](./src/main.cpp): Change the minor version from 1 to 6.
<br /> 
`glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);`
