uniform sampler2DArray u_terrain_samplers;
uniform uint u_selected_id;

void main()
{
    vec4 mask = texture(u_terrain_samplers, vec3(vertex_data.tex_coord, 0));
    
    vec4 grass_diff_color = texture(u_terrain_samplers, vec3(vertex_data.tex_coord * 10.0, 1));
    vec4 ground_diff_color = texture(u_terrain_samplers, vec3(vertex_data.tex_coord * 75.0, 2));

    vec3 grass_normal = texture(u_terrain_samplers, vec3(vertex_data.tex_coord * 10.0f, 3)).rgb;
    vec3 ground_normal = texture(u_terrain_samplers, vec3(vertex_data.tex_coord * 75.0f, 4)).rgb;

    vec4 mix_color = mix(grass_diff_color, ground_diff_color, mask.r);
    vec3 mix_normal = mix(grass_normal, ground_normal, mask.r);

    if(u_selected_id == entity_id && u_selected_id != uint(-1))
      mix_color = OutlineEffect(mix_color, vec4(1.0, 0.0, 0.0, 1.0), vertex_data.eye_position, vertex_data.eye_normal);
    Draw(mix_color, vec4(vertex_data.world_position, 1.0), vec4(normalize(mix_normal * vertex_data.world_normal), 1.0));
}