void main() 
{
  uint diffuse_index = materials_[material_index].a_diffuse_index;
  if(diffuse_index == uint(-1))
    Draw(vec4(1.0), vec4(vertex_data.world_position, 1.0), vec4(vertex_data.world_normal, 1.0));
  else
  {
    vec4 diffuse_color = texture(u_diffuse_texture, vec3(vertex_data.tex_coord, diffuse_index));
    Draw(diffuse_color, vec4(vertex_data.world_position, 1.0), vec4(vertex_data.world_normal, 1.0));
  }

  // Draw(vec4(materials_[material_index].a_diffuse, 1.0));
}
