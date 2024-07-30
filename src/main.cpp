#include <engine/jam_engine.h>

static f32 win_x = 16 * 75;
static f32 win_y = 9 * 75;

void UserInit(s32 argc, byte *argv[], void *) { PRINT_ARGS }

void UserUpdate(void *) {}

void UserClean(void *) {}

s32 main(s32 argc, byte *argv[])
{
  JAM_Engine::Config config = {argc, argv, static_cast<s32>(win_x), static_cast<s32>(win_y), false, false, true};
  JAM_Engine::Init(UserInit, config);
  JAM_Engine::Update(UserUpdate);
  JAM_Engine::Clean(UserClean);

  return 0;
}