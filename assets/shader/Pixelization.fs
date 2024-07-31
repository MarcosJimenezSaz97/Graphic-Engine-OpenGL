uniform sampler2D u_screen;
uniform float u_block_size = 7;

in vec2 uv;

void main()
{
  vec2 texSize = textureSize(u_screen, 0);

  vec2 blockUV = vec2(floor(uv.x * texSize.x / u_block_size) + 0.5, floor(uv.y * texSize.y / u_block_size) + 0.5);

  fragColor = texture(u_screen, blockUV * u_block_size / texSize);
}
