#include <unordered_map>

#include "engine/texture.h"
#include "math/mathlib.h"
#include "types.h"

#ifdef _WIN32
#include <tiny_obj_loader.h>
#elif __linux__
#include <tiny_obj/tiny_obj_loader.h>
#endif

#ifndef __MESH_H__
#define __MESH_H__ 1

/**
 * @brief Forward declaration of the Shader class.
 */
class Shader;

/**
 * @struct Vertex
 *
 * @brief Represents a 3D vertex with position, normal, and texture coordinates.
 */
struct Vertex
{
  Math::Vec3 position_;  ///< 3D position of the vertex.
  Math::Vec3 normal_;    ///< Normal vector of the vertex.
  Math::Vec2 texCoords_; ///< Texture coordinates of the vertex.
};

/**
 * @brief Struct representing material properties for a vertex.
 */
struct VertexMaterial
{
  Math::Vec3 ambient_ = 0.0f;                 ///< Ambient color of the material.
  u32 ambient_index = UINT32_MAX; ///< Ambient texture index.

  Math::Vec3 diffuse_ = 0.0f;                 ///< Diffuse color of the material.
  u32 diffuse_index = UINT32_MAX; ///< Diffuse texture index.

  Math::Vec3 specular_ = 0.0f;                 ///< Specular color of the material.
  u32 specular_index = UINT32_MAX; ///< Specular texture index.

  Math::Vec3 transmittance_ = 0.0f;                      ///< Transmittance color of the material.
  u32 specular_highlight_index = UINT32_MAX; ///< Specular highlight texture index.

  Math::Vec3 emission_ = 0.0f;                 ///< Emission color of the material.
  u32 emissive_index = UINT32_MAX; ///< Emissive texture index.

  f32 shininess_ = 0.0f; ///< Shininess of the material.
  f32 ior_ = 0.0f;       ///< Index of refraction of the material.
  f32 dissolve_ = 0.0f;  ///< Dissolve factor of the material.
  s32 illum_ = 0;      ///< Illumination model of the material.

  u32 bump_index = UINT32_MAX;         ///< Bump texture index.
  u32 displacement_index = UINT32_MAX; ///< Displacement texture index.
  u32 alpha_index = UINT32_MAX;        ///< Alpha texture index.
  u32 reflection_index = UINT32_MAX;   ///< Reflection texture index.

  u32 roughness_index = UINT32_MAX; ///< Roughness texture index.
  u32 metallic_index = UINT32_MAX;  ///< Metallic texture index.
  u32 sheen_index = UINT32_MAX;     ///< Sheen texture index.
  u32 normal_index = UINT32_MAX;    ///< Normal texture index.
};

/**
 * @struct CustomMesh
 *
 * @brief Structure representing a custom mesh.
 */
struct CustomMesh
{
  u32 *indices_ = nullptr;                      ///< Pointer to an array of indices
  u32 indices_size_ = 0;                        ///< Size of the indices array
  Vertex *vertices_ = nullptr;                  ///< Pointer to an array of vertices.
  VertexMaterial *vertices_material_ = nullptr; ///< Pointer to an array of vertices materials.
  u32 vertices_size_ = 0;                       ///< Size of the vertices array.
  boolean has_mesh_ = false;                    ///< Flag indicating whether the mesh has been successfully created.
};

/**
 * @brief Enum representing different drawing modes.
 */
enum class DrawMode : s16
{
  Points = 0, ///< Draw points.
  Lines,      ///< Draw lines.
  Triangles,  ///< Draw triangles.
};

/**
 * @brief Enum representing different culling modes.
 */
enum class CullMode : s16
{
  Front = 0,    ///< Cull front faces.
  Back,         ///< Cull back faces.
  FrontAndBack, ///< Cull both front and back faces.
};

/**
 * @brief Enum representing different front-face culling modes.
 */
enum class CullFront : s16
{
  Clockwise = 0,    ///< Cull clockwise faces.
  CounterClockwise, ///< Cull counterclockwise faces.
};

/**
 * @brief Configuration for drawing operations.
 */
struct DrawConfig
{
  DrawMode mode_ = DrawMode::Triangles; ///< The drawing mode.

  boolean active_culling_ = true;             ///< Flag indicating whether culling is active.
  CullMode cll_mode_ = CullMode::Back;        ///< The culling mode.
  CullFront cll_face_ = CullFront::Clockwise; ///< The front-face culling mode.
};

/**
 * @class Mesh
 *
 * @brief Class for handling 3D meshes.
 */
class Mesh
{
  friend class JAM_Engine; ///< Friend class.

public:
  /**
   * @enum Platonic
   *
   * @brief Enumeration representing Platonic shapes.
   */
  enum class Platonic : s16
  {
    // 2D - Forms
    k_Triangle = 0,  ///< Triangle shape.
    k_Quad,          ///< Quad shape.
    k_Circunference, ///< Circumference shape.

    // 3D - Forms
    k_Pyramid, ///< Pyramid shape.
    k_Cube,    ///< Cube shape.
    k_Sphere,  ///< Sphere shape.
    k_Capsule, ///< Capsule shape.

    k_MaxForms, ///< Maximum number of Platonic shapes.
  };

  /**
   * @brief Typedefinition for the Id type used in the Mesh class.
   */
  typedef uint32_t Id;

  /**
   * @brief Constructor for creating an empty Mesh.
   *
   * Constructor to load a mesh from an OBJ file.
   */
  Mesh();

  /**
   * @brief Destructor
   */
  ~Mesh();

  /**
   * @brief for releasing resources associated with the Mesh.
   */
  void free();

  /**
   * @brief Renders the mesh.
   */
  void render(DrawConfig dr_config) const;

  /**
   * @brief Checks if the mesh has been loaded.
   *
   * @return True if the mesh has been loaded, false otherwise.
   */
  boolean hasMesh() const;

  /**
   * @brief Loads a mesh from an OBJ file.
   *
   * Function to load a mesh from an OBJ file.
   *
   * @param filePath The path to the OBJ file.
   * @param normalize Flag to center and normalize de mesh
   *
   * @param wrapS Configuration for mesh textures
   * @param wrapT Configuration for mesh textures
   * @param minF Configuration for mesh textures
   * @param magF Configuration for mesh textures
   *
   * All textures configurations need to be at least 13 or nullptr.
   * The order is the same as VertexMaterial taking only the texture_index vars
   */
  void loadMesh(const std::string &filePath, boolean normalize, Texture::Wrap *wrapS = nullptr, Texture::Wrap *wrapT = nullptr, Texture::Filter *minF = nullptr, Texture::Filter *magF = nullptr);

  /**
   * @brief Loads a custom mesh using a user-defined callback.
   *
   * @param load_mesh_callback A callback function to load the mesh.
   */
  void loadCustomMesh(CustomMesh *(*load_mesh_callback)());

  /**
   * @brief Binds the material textures to opengl
   *
   * @param the program
   */
  void bindMaterialTextures(Shader *mtl, u32 texture_unit);

  /**
   * @brief Gets a vertex at the specified index.
   *
   * @param index The index of the vertex to retrieve.
   *
   * @return const Vertex The vertex at the specified index.
   */
  const Vertex getVertice(const size_t index) const;

  /**
   * @brief Gets the size of the vertices array.
   *
   * @return const u32 The size of the vertices array.
   */
  u32 verticesSize() const;

private:
  mutable u32 VAO, VBO, EBO, SSBO;    ///< Vertex Array Object (VAO), Vertex Buffer Object (VBO) and Elements Buffer Object (EBO) for rendering.
  boolean has_mesh_;                  ///< Flag indicating whether the mesh has been loaded.
  u32 *indices_;                      ///< Array of indices
  u32 indices_size_;                  ///< Sizeo of array indices
  u32 vertices_size_;                 ///< Size of the vertices array.
  Vertex *vertices_;                  ///< Array of vertices representing the mesh.
  VertexMaterial *vertices_material_; ///< Array of vertices representing the mesh.

  Texture::Wrap wrapS_[13];                                ///< Array of wrap modes for the S coordinate of textures.
  Texture::Wrap wrapT_[13];                                ///< Array of wrap modes for the T coordinate of textures.
  Texture::Filter minF_[13];                               ///< Array of minification filters for textures.
  Texture::Filter magF_[13];                               ///< Array of magnification filters for textures.
  mutable u32 texture_ids_[13];                            ///< Array of texture IDs.
  std::unordered_map<std::string, u32> textures_path_[13]; ///< Array of maps associating texture paths with texture IDs.

  /**
   * @brief Loads the buffers for rendering the mesh.
   */
  void loadBuffers() const;

  /**
   * @brief Loads the buffers for rendering the mesh.
   */
  void loadTextureBuffers() const;

  /**
   * @brief Centers and normalize the mesh within the given bounding box.
   *
   * @param min Minimum corner of the bounding box.
   * @param max Maximum corner of the bounding box.
   */
  void centerAndNormalize(Math::Vec3 min, Math::Vec3 max);
};

#endif /* __MESH_H__ */