#include <engine/jam_engine.h>
#include <cstdlib>

static f32 win_x = 16 * 75;
static f32 win_y = 9 * 75;

static const Camera::CamConfig config = {
    .light_render_type_ = Camera::LightRenderType::Deferred,
    .cam_win_ = Math::Vec2(win_x, win_y),
    .pos_ = Math::Vec3(0.0f, 10.0f, 10.0f),
    .target_ = Math::Vec3::zero,
    .GetMesh = &JAM_Engine::GetMesh,
    .UploadMesh = &JAM_Engine::UploadCustomMesh,
    .WheelScroll = &JAM_Engine::WheelScroll,
    .MousePosition = &JAM_Engine::MousePosition,
    .KeyInputPress = &JAM_Engine::InputPress,
    .MouseInputPress = &JAM_Engine::InputPress};

static Camera camera;

static Mesh *terrain = nullptr;
static Shader *terrain_shader = nullptr;
static Entity::Id terrain_id = static_cast<Entity::Id>(-1);

static Shader* lamp_shader = nullptr;
static Mesh* lamp = nullptr;
static Entity::Id lamp_id = static_cast<Entity::Id>(-1);

static Math::Vec3 light_dir(-1.0f);

static Shader* tree_shader = nullptr;
static Mesh* tree = nullptr;
static const int total_trees = 100;
static Entity::Id trees_id[total_trees] = { static_cast<Entity::Id>(-1) };

static const u32 total_forst_mtls = 5;

static u32 selected_entity = UINT32_MAX;

static const std::string forest_mtls[total_forst_mtls] = { OBJ("terrain/ground_path_mask.png"), 
                                                           OBJ("terrain/aerial_grass_rock_4k/aerial_grass_rock_diff_4k.jpg"), OBJ("terrain/forrest_ground_03_4k/forrest_ground_03_diff_4k.jpg"), 
                                                           OBJ("terrain/aerial_grass_rock_4k/aerial_grass_rock_nor_gl_4k.png"), OBJ("terrain/forrest_ground_03_4k/forrest_ground_03_nor_gl_4k.png")};

static TexturesArray* terrain_textures;

static inline boolean ValidIndex(const u_byte* data, const Math::Vec2& uv, const s32 width, const s32 height, const s32 channels)
{
  s32 x = static_cast<s32>(uv.x * static_cast<f32>(width));
  s32 y = static_cast<s32>(uv.y * static_cast<f32>(height));

  if (x < 0 || x >= width || y < 0 || y >= height)
    return false;

  size_t index = static_cast<size_t>((y * width + x) * channels);

  return !(data[index] > 0 && data[index + 1] > 0 && data[index + 2] > 0);
}

static inline size_t GetGrassIndex(const Mesh* obj, const size_t total_vertices, const u_byte* img, const s32 channels, const s32 width, const s32 height)
{
  size_t index = static_cast<size_t>(RAND_FLOAT(0.0f, static_cast<f32>(total_vertices)));
  Vertex vertice = obj->getVertice(index);
  while (!ValidIndex(img, vertice.texCoords_, width, height, channels))
  {
    index = static_cast<size_t>(RAND_FLOAT(0.0f, static_cast<f32>(total_vertices)));
    vertice = obj->getVertice(index);
  }
  return index;
}

static Source::Id crickets_background;
static Source::Id zelda_background;

static PointLight* p_light_ptr = nullptr;


void UserInit(s32 argc, byte *argv[], void *)
{
  PRINT_ARGS;
  camera.init(config);

  Texture::Wrap wrap[13] = { Texture::Wrap::Repeat };
  Texture::Filter filter[13] = { Texture::Filter::Nearest_Mipmap_Nearest };

  // Mesh
  terrain = JAM_Engine::GetMesh(JAM_Engine::UploadMesh(OBJ("terrain/Terrain.obj"), false));
  tree = JAM_Engine::GetMesh(JAM_Engine::UploadMesh(OBJ("tree/tree.obj"), false, wrap, wrap, filter, filter));
  lamp = JAM_Engine::GetMesh(JAM_Engine::UploadMesh(OBJ("stone_lamp/stone_lamp.obj"), false, wrap, wrap, filter, filter));

  // Material
  terrain_shader = JAM_Engine::GetShader(JAM_Engine::UploadShader(SHADER("terrain.fs"), SHADER("terrain.vs")));
  tree_shader = JAM_Engine::GetShader(JAM_Engine::UploadShader(SHADER("tree.fs"), SHADER("tree.vs")));
  lamp_shader = JAM_Engine::GetShader(JAM_Engine::UploadShader(SHADER("lamp.fs"), SHADER("lamp.vs")));
 
  Transform tr[total_trees + 1];
  Transform tr_lamp;
  DrawConfig dr_config;
  
  tr_lamp.scale(Math::Vec3(1.0f));
  tr_lamp.translate(Math::Vec3(-8.0f, 2.0f, 8.0f));
  tr[0].scale(Math::Vec3(1.0f));

  dr_config.cll_face_ = CullFront::CounterClockwise;
  TexturesArray::Id terrain_materials_ids = JAM_Engine::UploadTexturesArray(forest_mtls, total_forst_mtls, TexturesArray::Wrap::Repeat, TexturesArray::Wrap::Repeat, TexturesArray::Filter::Nearest_Mipmap_Nearest, TexturesArray::Filter::Nearest_Mipmap_Nearest);

  terrain_textures = JAM_Engine::GetTexturesArray(terrain_materials_ids);

  terrain_id = EM->newEntity("Terrain");
  EM->setComponent(terrain_id, terrain_shader);
  EM->setComponent(terrain_id, terrain);
  EM->setComponent(terrain_id, tr[0]);
  EM->setComponent(terrain_id, dr_config);

  lamp_id = EM->newEntity("Lamp");
  EM->setComponent(lamp_id, lamp_shader);
  EM->setComponent(lamp_id, lamp);
  EM->setComponent(lamp_id, tr_lamp);
  EM->setComponent(lamp_id, dr_config);

  while (!terrain->hasMesh())
    ;

  u32 total_vertices = terrain->verticesSize();

  Texture path_mask;
  path_mask.loadTexture(OBJ("terrain/ground_path_mask.png"));

  const s32 channels = path_mask.channels();
  const s32 width = path_mask.width();
  const s32 height = path_mask.height();
  const u_byte* path_mask_data = path_mask.data();

  for (u32 i = 0; i < total_trees; i++)
  {
    size_t index = GetGrassIndex(terrain, total_vertices, path_mask_data, channels, width, height);
    Vertex vertex = terrain->getVertice(index);
    tr[i+1].scale(Math::Vec3(1.0f));
    tr[i+1].translate(Math::Vec3(vertex.position_));

    std::string tree_names = std::string("Tree_") + std::to_string(i);
    trees_id[i] = EM->newEntity(tree_names.c_str());
    EM->setComponent(trees_id[i], tree_shader);
    EM->setComponent(trees_id[i], tree);
    EM->setComponent(trees_id[i], tr[i+1]);
    EM->setComponent(trees_id[i], dr_config);
  }

  path_mask.free();

  //Sound
  f32 pos[3] = { camera.getPosition().x, camera.getPosition().y, camera.getPosition().z  };
  f32 vel[3] = { 0.0f };
  crickets_background = SC->uploadSound((byte*)MUSIC("grillos.wav"), 1.0f, 0.3f, pos, vel, true);
  zelda_background = SC->uploadSound((byte*)MUSIC("BOTW.wav"), 1.0f, 1.0f, pos, vel, true);
  SC->play(crickets_background);
  SC->play(zelda_background);

  //Lights
  PointLight point_light;

  point_light.bright_ = 0.5f;
  point_light.specular_str_ = 0.0f;
  point_light.specular_bright_ = 16.0f;
  point_light.linear_attenuation_ = 0.025f;
  point_light.constant_attenuation_ = 0.01f;
  point_light.quadratic_attenuation_ = 0.001f;
  point_light.use_volumetric_ = true;

  point_light.position_ = Math::Vec3(-8.0f, 5.0f, 8.0f);
  // point_light.difuse_clr_ = Math::Vec3::one / 2.0f;
  point_light.difuse_clr_ = Math::Vec3(0.5f, 0.75f, 0.5f);
  point_light.active_ = true;
  p_light_ptr = JAM_Engine::GetPointLight(JAM_Engine::AddLight(point_light));
}

void UserUpdate(void*)
{
  camera.control(JAM_Engine::DeltaTime());

  if (JAM_Engine::InputDown(Inputs::Key::Key_F5))
    JAM_Engine::RechargeShaders();

  JAM_Engine::BeginRenderShadow(0, LightType::PointLight);
  JAM_Engine::RenderShadow(lamp_id);
  JAM_Engine::RenderShadow(terrain_id);
  for (int i = 0; i < total_trees; i++)
    JAM_Engine::RenderShadow(trees_id[i]);
  JAM_Engine::EndRenderShadow();

  terrain_shader->use();
  terrain_shader->setTexture2DArray("u_terrain_samplers", terrain_textures->id(), 13);
  JAM_Engine::BeginRender(&camera);
  JAM_Engine::Render(lamp_id);
  JAM_Engine::Render(terrain_id);
  for (int i = 0; i < total_trees; i++)
    JAM_Engine::Render(trees_id[i]);
  JAM_Engine::EndRender();

  if (JAM_Engine::InputDown(Inputs::MouseButton::Mouse_Button_Left))
  {
    selected_entity = camera.getSelectedEntityId();
    fprintf(stdout, "Selected entity %d\n", selected_entity);
    terrain_shader->use();
    terrain_shader->setU32("u_selected_id", selected_entity);
    lamp_shader->use();
    lamp_shader->setU32("u_selected_id", selected_entity);
    tree_shader->use();
    tree_shader->setU32("u_selected_id", selected_entity);
  }
}

void UserClean(void *) {}

s32 main(s32 argc, byte *argv[])
{
  JAM_Engine::Config config = {
      argc, argv,
      static_cast<s32>(win_x),
      static_cast<s32>(win_y),
      false, true, true,
      ShadowsManager::Resolution::High,
      ShadowsManager::Resolution::Low,
      ShadowsManager::Resolution::High };
  JAM_Engine::Init(UserInit, config);
  JAM_Engine::Update(UserUpdate);
  JAM_Engine::Clean(UserClean);

  return 0;
}
