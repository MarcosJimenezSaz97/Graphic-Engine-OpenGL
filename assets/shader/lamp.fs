uniform uint u_selected_id;

void main()
{
  vec4 color = vec4(1.0);
  uint diffuse_index = materials_[material_index].a_diffuse_index;
  if(diffuse_index != uint(-1))
    color = texture(u_diffuse_texture, vec3(vertex_data.tex_coord, diffuse_index));

  vec3 normal = vertex_data.world_normal;
  uint normal_index = materials_[material_index].a_normal_index;
  if(normal_index != uint(-1))
    normal *= texture(u_normal_texture, vec3(vertex_data.tex_coord, normal_index)).rgb;

  vec3 displacement = vertex_data.world_position;
  uint displacement_index = materials_[material_index].a_displacement_index;
  if(displacement_index != uint(-1))
    displacement += texture(u_displacement_texture, vec3(vertex_data.tex_coord, displacement_index)).rgb;

  if(u_selected_id == entity_id && u_selected_id != uint(-1))
    color = OutlineEffect(color, vec4(1.0, 0.0, 0.0, 1.0), vertex_data.eye_position, vertex_data.eye_normal);
  Draw(color, vec4(displacement, 1.0), vec4(normalize(normal), 1.0));
}