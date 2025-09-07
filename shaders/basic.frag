#version 330 core

uniform sampler2D tex;

in vec3 colour;
in vec2 tex_coord;

out vec4 frag_colour;

void main() {
    frag_colour = texture(tex, tex_coord) * vec4(colour, 1.0);
}

