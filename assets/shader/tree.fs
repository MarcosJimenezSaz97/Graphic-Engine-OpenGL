uniform uint u_selected_id;

void main()
{
  vec4 color = vec4(1.0);
  uint diffuse_index = materials_[material_index].a_diffuse_index;
  if(diffuse_index != uint(-1))
    color = texture(u_diffuse_texture, vec3(vertex_data.tex_coord, diffuse_index));

  if(u_selected_id == entity_id && u_selected_id != uint(-1))
    color = OutlineEffect(color, vec4(1.0, 0.0, 0.0, 1.0), vertex_data.eye_position, vertex_data.eye_normal);
  Draw(color, vec4(vertex_data.world_position, 1.0), vec4( vertex_data.world_normal, 1.0));
}