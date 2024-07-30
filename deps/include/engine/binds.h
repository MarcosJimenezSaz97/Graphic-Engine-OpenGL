#include <string>

#ifndef __BINDS_H__
#define __BINDS_H__ 1

/**
 * @brief The engine use this binds for SHADER STORAGE BUFFER.
 * It's recommended not to use them for your own data
*/

// Shader storage buffer
///////////////////////////////////////////////////////////////////////////////
#define POINT_LIGHT_BIND 0
#define SPOT_LIGHT_BIND 1
#define DIRECTIONAL_LIGHT_BIND 2
#define VERTEX_MATERIAL_BIND 3
///////////////////////////////////////////////////////////////////////////////

// Samplers bind
///////////////////////////////////////////////////////////////////////////////
#define TOTAL_ENGINE_TEXTURES_BIND 13 // The first 13 are the used for vertex materials
///////////////////////////////////////////////////////////////////////////////

static const std::string binds = R"(
#define POINT_LIGHT_BIND 0
#define SPOT_LIGHT_BIND 1
#define DIRECTIONAL_LIGHT_BIND 2
#define VERTEX_MATERIAL_BIND 3
)";

#endif /* __BINDS_H__ */