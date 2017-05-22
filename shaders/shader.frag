#version 330 core

in vec2 TexCoords;

out vec4 outColour;

uniform sampler2D image;
uniform vec3 fragColour;

void main() {
  outColour = vec4(fragColour, 1.0f) * texture(image, TexCoords);
}
