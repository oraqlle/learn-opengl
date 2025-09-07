#version 330 core

uniform sampler2D tex0;
uniform sampler2D tex1;

in vec3 colour;
in vec2 tex_coord;

out vec4 frag_colour;

void main() {
    frag_colour = mix(texture(tex0, tex_coord), texture(tex1, tex_coord), 0.2);
}

