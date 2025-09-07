#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 in_colour;
layout (location = 2) in vec2 in_tex_coord;

out vec3 colour;
out vec2 tex_coord;

void main() {
    gl_Position = vec4(pos, 1.0);
    colour = in_colour;
    tex_coord = in_tex_coord;
}

