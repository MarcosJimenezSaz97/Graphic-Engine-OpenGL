#include "math/mathlib.h"
#include "inputs.h"
#include "types.h"

#include "shader.h"
#include "mesh.h"

#ifndef __CAMERA_H__
#define __CAMERA_H__ 1

/**
 * @class Camera
 *
 * @brief Class that represents a camera.
 *
 * This class provides functionality for working with cameras,
 * including configuration and related operations.
 */
class Camera
{
public:
  /**
   * @enum TextureData
   *
   * @brief Enumeration for texture types
   */
  enum TextureDataType : u32
  {
    Colour = 0, ///< Colour texture data.
    Location,   ///< Location texture data.
    Normals,    ///< Normals texture data.
    Picker,     ///< Picker texture data.

    MaxTextures, ///< Maximum number of texture types.
  };

  /**
   * @enum Type
   *
   * @brief Enumerator that represents the type of camera.
   */
  enum class RenderType : u32
  {
    Invalid = 0, ///< Invalid rendering type.
    /**
     * @brief Orthographic camera type.
     *
     * Create a cubic perspective for the camera view.
     */
    Orthographic,

    /**
     * @brief Tipo de cámara perspectiva.
     *
     * Create a frustum perspective for the camera view.
     */
    Perspective
  };

  /**
   * @enum Type
   *
   * @brief Enumerator that represents the type of camera.
   */
  enum class LightRenderType : u32
  {
    Invalid = 0, ///< Invalid light rendering type.
    /**
     * @brief Use deffer rendering
     */
    Deferred,

    /**
     * @brief Use forward rendering
     */
    Forward
  };

  /**
   * @struct CamConfig
   *
   * @brief Structure that defines the camera configuration.
   *
   * This structure contains parameters that define the configuration of a
   * camera.
   */
  struct CamConfig
  {
    RenderType camera_render_type_ = RenderType::Perspective;       ///< Camera type.
    LightRenderType light_render_type_ = LightRenderType::Deferred; ///< Lights Type.

    Math::Vec2 cam_win_; ///< Camera window size.
    Math::Vec3 pos_;     ///< Camera position in three-dimensional space.
    Math::Vec3 target_;  ///< Point the camera is pointing at.

    f32 near_ = 1.0f;   ///< Close distance for the camera.
    f32 far_ = 1000.0f; ///< Far distance for the camera.

    f32 right_ = 10.0f;   ///< Parameter used for the orthographic view.
    f32 left_ = -10.0f;   ///< Parameter used for the orthographic view.
    f32 top_ = 10.0f;     ///< Parameter used for the orthographic view.
    f32 bottom_ = -10.0f; ///< Parameter used for the orthographic view.

    f32 fovy_ = Math::MathUtils::AngleToRads(60.0f); ///< Angle of view inradians for perspective view.

    /**
     * @brief Function pointer to retrieve a Mesh by its ID.
     *
     * @param id The ID of the Mesh to retrieve.
     *
     * @return A pointer to the Mesh.
     */
    Mesh *(*GetMesh)(Mesh::Id);

    /**
     * @brief Function pointer to upload a Mesh using a custom load callback.
     *
     * @param load_mesh_callback A callback function to load the CustomMesh.
     *
     * @return The ID of the uploaded Mesh.
     */
    Mesh::Id (*UploadMesh)(CustomMesh *(*load_mesh_callback)());

    /**
     * @brief Function pointer to get the current wheel scroll position.
     *
     * @return A Math::Vec2 representing the wheel scroll position.
     */
    Math::Vec2 (*WheelScroll)();

    /**
     * @brief Function pointer to get the current mouse position.
     *
     * @return A Math::Vec2 representing the mouse position.
     */
    Math::Vec2 (*MousePosition)();

    /**
     * @brief Function pointer to check if a key is currently pressed.
     *
     * @param key The key to check.
     *
     * @return true if the key is pressed, false otherwise.
     */
    boolean (*KeyInputPress)(Inputs::Key);

    /**
     * @brief Function pointer to check if a mouse button is currently pressed.
     *
     * @param button The mouse button to check.
     *
     * @return true if the mouse button is pressed, false otherwise.
     */
    boolean (*MouseInputPress)(Inputs::MouseButton);
  };

  /**
   * @brief To change to desired key: camera_object.front_move_key_ = static_cast<u32>(Inputs::Key::...);
   */
  Inputs::Key front_move_key_; ///< Key for moving the camera forward.
  Inputs::Key back_move_key_;  ///< Key for moving the camera backward.
  Inputs::Key right_move_key_; ///< Key for moving the camera to the right.
  Inputs::Key left_move_key_;  ///< Key for moving the camera to the left.
  Inputs::Key up_move_key_;    ///< Key for moving the camera upward.
  Inputs::Key down_move_key_;  ///< Key for moving the camera downward.

  /**
   * @brief Constructor of the Camera class.
   */
  Camera();

  /**
   * @brief Initialize the camera configuration.
   *
   * Need to call after window init.
   *
   * @param config Configuration of the camera to use.
   */
  void init(CamConfig config);

  /**
   * @brief Destructor of the Camera class.
   *
   * Release the created camera.
   */
  ~Camera();

  /**
   * @brief Updates the camera.
   *
   * @param dt Delta time for constant movement
   */
  void control(const f32 dt);

  /**
   * @brief Gets the type of the camera.
   *
   * @return Camera type.
   */
  RenderType getRenderType() const;

  /**
   * @brief Gets the type of the light render.
   *
   * @return Light render type.
   */
  LightRenderType getLightRenderType() const;

  /**
   * @brief Sets the initial position of the camera window.
   *
   * This function assigns the initial position of the camera window using
   * the specified coordinates.
   *
   * @param win_pos Initial position of the camera window (x, y coordinates).
   */
  void setWinPos(Math::Vec2 win_pos);

  /**
   * @brief Gets the initial position of the camera window.
   *
   * This function returns the starting position of the camera window as
   * a Math::Vec2 object.
   *
   * @return Initial position of the camera window (x, y coordinates).
   */
  Math::Vec2 winPos() const;

  /**
   * @brief Gets the size of the camera window.
   *
   * This function returns the camera window size as
   * a Math::Vec2 object.
   *
   * @return Size of the camera window (x, y coordinates).
   */
  Math::Vec2 winSize() const;

  /**
   * @brief Sets the size of the camera window.
   *
   * This function assigns the camera window size as
   * a Math::Vec2 object.
   *
   * @param size Size of the camera window (x, y coordinates).
   */
  void setWinSize(Math::Vec2 size);

  /**
   * @brief Gets the perspective projection matrix associated with the current camera settings.
   *
   * This function returns the perspective projection matrix calculated from
   * the current camera settings, which includes parameters such as position,
   * orientation, and window aspect.
   *
   * @return Perspective projection matrix.
   */
  Math::Mat4 getPerspectiveMatrix() const;

  /**
   * @brief Gets the orthographic projection matrix associated with the current camera settings.
   *
   * This function returns the orthographic projection matrix calculated from
   * the current camera settings, which includes parameters such as position,
   * orientation, and window dimensions.
   *
   * @return Orthographic projection matrix.
   */
  Math::Mat4 getOrtoMatrix() const;

  /**
   * @brief Gets the view array associated with the current camera settings.
   *
   * This function returns the view matrix calculated from the current camera
   * settings, which includes parameters such as position, orientation, and
   * focus point.
   *
   * @return View matrix.
   */
  Math::Mat4 getViewMatrix() const;

  /**
   * @brief Gets the position of the camera.
   *
   * @return Camera Position.
   */
  Math::Vec3 getPosition() const;

  /**
   * @brief Set the position of the camera.
   *
   * @param pos Camera new position.
   */
  void setPosition(Math::Vec3 pos);

  /**
   * @brief Gets the direction of the camera.
   *
   * @return Camera Direction.
   */
  Math::Vec3 getViewDir() const;

  /**
   * @brief Set the target of the camera.
   *
   * @param target Camera new target.
   */
  void setTarget(Math::Vec3 target);

  /**
   * @brief Bind the camera buffers
   * Used internally
   */
  void beginRender();

  /**
   * @brief Activate the camera buffer
   * Used internally
   */
  Shader *getMaterial();

  /**
   * @brief Render the camera buffer
   * Used internally
   */
  void render();

  /**
   * @brief Sets the material for post-processing.
   *
   * @param mat Pointer to the Shader object representing the post-processing material.
   */
  void setMatPostProcess(Shader *mat);

  /**
   * @brief Gets the ID of the selected entity.
   *
   * @return u32 The ID of the selected entity.
   */
  u32 getSelectedEntityId();

private:
  /**
   * @brief Generates textures to save screen data
   */
  boolean initTextures();

  /**
   * @brief Move the camera.
   *
   * Adjust the camera's position according to keyboard commands.
   *
   * @param dt Delta time for constant movement
   */
  void move(const f32 dt);

  /**
   * @brief Rotate the camera (Keyboard).
   *
   * Adjust the camera's rotation according to keyboard commands.
   *
   * @param dt Delta time for constant movement
   *
   */
  void rotate(const f32 dt);

  /**
   * @brief Rotate the camera (Mouse).
   *
   * Adjust the camera's rotation according to mouse movement.
   *
   * @param dt Delta time for constant movement
   *
   */
  void mouseRotate(const f32 dt);

  RenderType render_type_;                  ///< Camera render type.
  LightRenderType light_type_;              ///< Light render type.
  Math::Vec3 camera_, target_;              ///< Camera position and focus point.
  Math::Vec3 view_dir_, side_dir_, up_dir_; ///< Camera directions.

  Math::Vec2 prev_mouse_;   ///< Mouse coordinates in the previous frame.
  f32 speed_, sensitivity_; ///< Camera speed and sensitivity.

  f32 near_, far_;                  ///< Near and far distances for the camera.
  f32 right_, left_, top_, bottom_; ///< Parameters for the orthographic view.
  f32 fov_, aspect_;                ///< Viewing angle and aspect ratio.

  Math::Vec2 window_pos_;    ///< Window position
  Math::Vec2 window_size_;   ///< Size of the camera window.
  Math::Vec2 textures_size_; ///< Size of the textures.

  ///< Light Material
  u32 fbo_;                                           ///< Frame buffer object.                        
  u32 depth_buffer_;                                  ///< depth buffer
  u32 textures_[TextureDataType::MaxTextures];        ///< Array of texture IDs.
  u32 attachments_[TextureDataType::MaxTextures];     ///< Array of attachment points for textures.
  u32 active_textures_[TextureDataType::MaxTextures]; ///< Array of active texture IDs.

  boolean is_initialized_; ///< Camera initialization status.

  Shader light_mat_; ///< Shader used for the light material.
  Mesh *quad_;       ///< Pointer to a mesh object representing a quad.

  ///< Post Process Material
  Shader *post_process_mat_;        ///< Pointer to the shader used for post-processing.
  u32 post_process_fbo_;            ///< Framebuffer object for post-processing.
  u32 post_process_texture_;        ///< Texture used in post-processing.
  u32 post_process_attachment_;     ///< Attachment point for the post-process texture.
  u32 post_process_active_texture_; ///< Active texture for post-processing.

  /**
   * @brief Function pointer to retrieve the mouse wheel scroll.
   *
   * @return Math::Vec2 The mouse wheel scroll values.
   */
  Math::Vec2 (*WheelScroll)();

  /**
   * @brief Function pointer to retrieve the current mouse position.
   *
   * @return Math::Vec2 The current mouse position.
   */
  Math::Vec2 (*MousePosition)();

  /**
   * @brief Function pointer to check if a specific key is pressed.
   *
   * @param key The key to check.
   *
   * @return true if the key is pressed, false otherwise.
   */
  boolean (*KeyInputPress)(Inputs::Key);

  /**
   * @brief Function pointer to check if a mouse button is pressed.
   *
   * @param button The mouse button to check.
   *
   * @return true if the mouse button is pressed, false otherwise.
   */
  boolean (*MouseInputPress)(Inputs::MouseButton);
};

#endif /* __CAMERA_H__ */