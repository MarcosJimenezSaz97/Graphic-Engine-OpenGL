out vec2 uv;

void main()
{
  gl_Position = vec4(a_position, 1.0);

  uv = a_tex_coords; 
}