#include "math/mathlib.h"
#include "types.h"

#ifndef __LIGHT_H__
#define __LIGHT_H__ 1

/**
 * @brief Enumerates different types of lights.
 */
enum class LightType : s16
{
  SpotLight,        ///< Spot light type.
  PointLight,       ///< Point light type.
  DirectionalLight, ///< Directional light type.
};

/**
 * @brief Enumerates directions for lights.
 *
 * Use the same direcctions as the Math Lib.
 */
enum class LightDirection : s16
{
  Front = 0, ///< Represents the front direction: (0, 0, 1).
  Back,      ///< Represents the back direction: (0, 0, -1).
  Up,        ///< Represents the up direction: (0, 1, 0).
  Down,      ///< Represents the down direction: (0, -1, 0).
  Right,     ///< Represents the right direction: (1, 0, 0).
  Left,      ///< Represents the left direction: (-1, 0, 0).

  Max ///< Represents the maximum number of directions.
};

/**
 * @struct PointLight
 *
 * @brief Structure representing a point light source in 3D space.
 */
struct PointLight
{
public:
  /**
   * @brief Type for point light identifier.
   */
  typedef uint32_t Id;

  /**
   * @brief Gets the view matrix for the camera.
   *
   * @param direction return the ViewMatrix for a concret direction
   * @return Math::Mat4 The view matrix.
   */
  Math::Mat4 getViewMatrix(LightDirection direction);

  /**
   * @brief Gets the perspective matrix for the camera.
   *
   * @return Math::Mat4 The perspective matrix.
   */
  Math::Mat4 getPerspectiveMatrix();

private:
  Math::Mat4 v_matrix_[6]; ///< View matrix of the spot light, used in shader for shadows
  Math::Mat4 p_matrix_;    ///< Perspective matrix of the spot light, used in shader for shadows

public:
  Math::Vec3 position_; ///< Position of the point light.
  f32 bright_;          ///< Brightness of the point light.

  Math::Vec3 difuse_clr_; ///< Diffuse color of the point light.
  f32 specular_str_;      ///< Specular strength of the point light.

  f32 quadratic_attenuation_; ///< Quadratic attenuation of the point light.
  f32 constant_attenuation_;  ///< Constant attenuation of the point light.
  f32 linear_attenuation_;    ///< Linear attenuation of the point light.
  u32 use_volumetric_;        ///< For Volumetric use

  Math::Vec2 padding_two = 0.0f; ///< Necesary for alignment
  u32 active_ = 1;               ///< Flag to turn on/off the light
  f32 specular_bright_;          ///< Specular brightness of the point light.
};

/**
 * @class SpotLight
 *
 * @brief Class representing a spot light source in 3D space.
 */
class SpotLight
{
public:
  /**
   * @brief Type for spot light identifier.
   */
  typedef uint32_t Id;

  /**
   * @brief Sets the position and direction for the light.
   *
   * @param pos The position vector.
   * @param dir The direction vector.
   */
  void setPosAndDir(Math::Vec3 pos, Math::Vec3 dir);

  /**
   * @brief Gets the view matrix for the camera.
   *
   * @return Math::Mat4 The view matrix.
   */
  Math::Mat4 getViewMatrix();

  /**
   * @brief Gets the perspective matrix for the camera.
   *
   * @return Math::Mat4 The perspective matrix.
   */
  Math::Mat4 getPerspectiveMatrix();

private:
  Math::Mat4 v_matrix_; ///< View matrix of the spot light, used in shader for shadows
  Math::Mat4 p_matrix_; ///< Perspective matrix of the spot light, used in shader for shadows

  Math::Vec3 position_; ///< Position of the spot light.

public:
  f32 bright_; ///< Brightness of the spot light.

private:
  Math::Vec3 direction_; ///< Direction of the spot light.

public:
  f32 cut_off_; ///< Cutoff angle of the spot light.

  Math::Vec3 difuse_clr_; ///< Diffuse color of the spot light.
  f32 specular_str_;      ///< Specular strength of the spot light.

  f32 linear_attenuation_;    ///< Linear attenuation of the spot light.
  f32 constant_attenuation_;  ///< Constant attenuation of the spot light.
  f32 quadratic_attenuation_; ///< Quadratic attenuation of the spot light.
  f32 outter_cut_off_;        ///< Outer cutoff angle of the spot light.

  u32 use_volumetric_;      ///< Flag for using volumetric light
  f32 empty_ = 0.0f;        ///< Empty to alignement
  f32 specular_bright_;     ///< Specular brightness of the spot light.
  u32 active_ = 1;          ///< Flag to turn on/off the light
};

/**
 * @class DirectionalLight
 *
 * @brief Class representing a directional light source in 3D space.
 */
class DirectionalLight
{
public:
  /**
   * @brief Type for directional light identifier.
   */
  typedef uint32_t Id;

  /**
   * @brief Sets the direction for a camera.
   *
   * @param dir The direction vector.
   */
  void setDirection(Math::Vec3 pos, Math::Vec3 dir);

  /**
   * @brief Gets the view matrix for the camera.
   *
   * @return Math::Mat4 The view matrix.
   */
  Math::Mat4 getViewMatrix();

  /**
   * @brief Gets the perspective matrix for the camera.
   *
   * @return Math::Mat4 The perspective matrix.
   */
  Math::Mat4 getPerspectiveMatrix();

private:
  Math::Mat4 v_matrix_; ///< View matrix of the directional light, used in shader for shadows
  Math::Mat4 p_matrix_; ///< Perspective matrix of the directional light, used in shader for shadows

  Math::Vec3 position_; ///< Position of the directional light.

public:
  f32 bright_; ///< Brightness of the directional light.

private:
  Math::Vec3 direction_; ///< Direction of the spot light.

public:
  f32 specular_bright_;       ///< Specular brightness of the spot light.
  Math::Vec3 difuse_clr_;     ///< Diffuse color of the spot light.
  f32 specular_str_;          ///< Specular strength of the spot light.
  u32 use_volumetric_;        ///< Flag for using volumetric light
  Math::Vec2 padding_ = 0.0f; ///< Necesary for alignment
  u32 active_ = 1;            ///< Flag to turn on/off the light
};

#endif /* __LIGHT_H__ */