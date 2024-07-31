uniform sampler2D shadow_map_;

void main() 
{
  vec3 final_light = vec3(0.0);

  vec4 world_position = texture(u_location_img, vertex_data.tex_coord);

  final_light += GetShadowFactor(directional_light_[0], shadow_map_) * GetLight(directional_light_[0], true) + GetVolumetricLight(spot_light[0], shadow_map_, 0, world_position.xyz, 0.5, 100.0f, 0.1));

  fragColor = vec4(final_light, 1.0);
}