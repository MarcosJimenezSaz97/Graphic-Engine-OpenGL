
out vec2 vertex_tex_coordinates;

void main() 
{
  gl_Position = GetWorldPosition();
  
  vertex_tex_coordinates = a_tex_coords;
}