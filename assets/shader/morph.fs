uniform sampler2D Image;
uniform vec2 Mouse_Pos;
uniform vec2 Screen;
uniform float Rotation_Angle; // Can be loops
const float Stretch_Factor = 5.0; // [0.5, 20.0]
const float Rotation_Radius = (1.0 / 1024.0) * 400.0; // [0, 1.0 / Screen]
const float Power = 1.5; // [1, 2]

vec2 rotate(vec2 point, vec2 origin, float angle) {
  float s = sin(angle);
  float c = cos(angle);

  // Trasladar el punto al origen
  point -= origin;

  // Aplicar la rotación
  float xnew = point.x * c - point.y * s;
  float ynew = point.x * s + point.y * c;

  // Trasladar el punto de vuelta
  point.x = xnew + origin.x;
  point.y = ynew + origin.y;

  return point;
}

vec2 transformUV(vec2 mouse, vec2 original_uv, float power) {
  vec2 delta = original_uv - mouse;
  return mouse + sign(delta) * pow(abs(delta), vec2(power));
}

vec2 stretchUV(vec2 mouse, vec2 uv, float factor) {
  vec2 delta = uv - mouse;
  float dist = length(delta);
  return mouse + delta * (1.0 + factor * exp(-dist * 10.0)); // Ajustar el valor 10.0 para controlar la caída
}

void main() {
  vec2 normalized_mouse = Mouse_Pos / Screen;
  vec2 morphed_tex_coord = transformUV(normalized_mouse, vertex_data.tex_coord, Power);

  // Aplicar el estiramiento en torno al ratón
  vec2 stretched_tex_coord = stretchUV(normalized_mouse, morphed_tex_coord, Stretch_Factor);

  // Calcular la distancia del texel al ratón
  float dist = length(stretched_tex_coord - normalized_mouse);

  // Calcular el factor de mezcla para la rotación
  float rotation_mix = smoothstep(Rotation_Radius, 0.0, dist);

  // Aplicar la rotación condicionalmente basada en la distancia
  vec2 rotated_tex_coord = mix(stretched_tex_coord, rotate(stretched_tex_coord, normalized_mouse, Rotation_Angle), rotation_mix);

  vec4 color = texture(Image, rotated_tex_coord);
  Draw(color, vec4(vertex_data.world_position, 1.0), vec4(vertex_data.world_normal, 1.0));
}
