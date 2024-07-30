#include "types.h"

#ifndef __GPUMANAGER_H__
#define __GPUMANAGER_H__ 1

/**
 * @class GPUResources
 */
class GPUResources
{
public:
  /**
   * @brief Instance a resource of the gpu.
   */
  static GPUResources *Instance();

  /**
   * @brief Free all resources
   */
  void free();

  /**
   * @brief Create a shader program and link it.
   *
   * @param fragmentSource Fragment shader source code.
   * @param vertexSource Vertex shader source code.
   *
   * @return Shader program identifier.
   */
  u32 CreateProgram(const byte *fragmentSource = nullptr, const byte *vertexSource = nullptr);

  /**
   * @brief Compile a shader.
   *
   * @param shaderType Shader type.
   * @param source Shader source code.
   *
   * @return Identifier of the compiled shader.
   */
  u32 CompileShader(u32 shaderType, const byte *source);

  /**
   * @brief Create a vertex array.
   *
   * @param count Count the total array.
   *
   * @return Identifier of the vertex array.
   */
  u32 *CreateVertexArrays(u32 count);

  /**
   * @brief Create OpenGL buffer objects.
   *
   * @param count The number of buffer objects to create.
   *
   * @return u32* Pointer to the array of buffer object IDs.
   */
  u32 *CreateBuffers(u32 count);

  /**
   * @brief Create OpenGL framebuffer objects.
   *
   * @param count The number of framebuffer objects to create.
   *
   * @return u32* Pointer to the array of framebuffer object IDs.
   */
  u32 *CreateFrameBuffers(u32 count);

  /**
   * @brief Create OpenGL renderbuffer objects.
   *
   * @param count The number of renderbuffer objects to create.
   *
   * @return u32* Pointer to the array of renderbuffer object IDs.
   */
  u32 *CreateRenderBuffers(u32 count);

  /**
   * @brief Create OpenGL texture objects.
   *
   * @param count The number of texture objects to create.
   *
   * @return u32* Pointer to the array of texture object IDs.
   */
  u32 *CreateTextures(u32 count);

private:
  /**
   * @brief Constructor for GPUResources class.
   */
  GPUResources();

  /**
   * @brief Destructor for GPUResources class.
   */
  ~GPUResources();

  u32 *programs_;     ///< Array of program IDs.
  u32 programs_size_; ///< Size of the programs array.

  u32 **vaos_;      ///< Array of vertex array object (VAO) IDs.
  u32 *vaos_sizes_; ///< Array storing the sizes of individual VAO arrays.
  u32 vaos_length_; ///< Length of the VAOs array.

  u32 **bos_;      ///< Array of buffer object (BO) IDs.
  u32 *bos_sizes_; ///< Array storing the sizes of individual BO arrays.
  u32 bos_length_; ///< Length of the BOs array.

  u32 **fbos_;      ///< Array of framebuffer object (FBO) IDs.
  u32 *fbos_sizes_; ///< Array storing the sizes of individual FBO arrays.
  u32 fbos_length_; ///< Length of the FBOs array.

  u32 **rbos_;      ///< Array of renderbuffer object (RBO) IDs.
  u32 *rbos_sizes_; ///< Array storing the sizes of individual RBO arrays.
  u32 rbos_length_; ///< Length of the RBOs array.

  u32 **textures_;      ///< Array of texture IDs.
  u32 *textures_sizes_; ///< Array storing the sizes of individual texture arrays.
  u32 textures_length_; ///< Length of the textures array.
};

/**
 * @brief Access the GPU Manager intance (GPUResources)
 */
#define GPU (GPUResources::Instance())

#endif /* __GPUMANAGER_H__ */