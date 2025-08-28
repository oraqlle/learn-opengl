#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 in_colour;

out vec3 colour;

void main() {
    gl_Position = vec4(pos, 1.0);
    colour = in_colour;
}

