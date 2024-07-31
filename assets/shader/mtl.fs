uniform sampler2D Image;

void main() 
{
  Draw(vec4(1.0), vec4(vertex_data.world_position, 1.0), vec4(vertex_data.world_normal, 1.0));
}
