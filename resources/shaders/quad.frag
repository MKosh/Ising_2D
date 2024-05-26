#version 450

out vec4 FragColor;

in vec2 tex_coord;

uniform float red;
uniform sampler2D Texture;

void main() {
  //FragColor = vec4(red, 0.5, 0.6, 1.0);
  FragColor = texture(Texture, tex_coord);
  if (FragColor.r > 0.5) {
    FragColor = vec4(1.0);
  } else {
    FragColor = vec4(0.0, 0.0, 0.0, 1.0);
  }
}
