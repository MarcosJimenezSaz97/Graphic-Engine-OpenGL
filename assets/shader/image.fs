uniform sampler2D Image;

void main() 
{
  vec4 texture_color = texture(Image, vertex_data.tex_coord);
  Draw(texture_color, vec4(vertex_data.world_position, 1.0), vec4(vertex_data.world_normal, 1.0));
}
