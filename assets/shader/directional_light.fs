uniform sampler2D shadow_map_;

void main() 
{
  vec3 final_light = vec3(0.0);

  final_light += GetShadowFactor(directional_light_[0], shadow_map_) * GetLight(directional_light_[0], true);

  fragColor = vec4(final_light, 1.0);
}
