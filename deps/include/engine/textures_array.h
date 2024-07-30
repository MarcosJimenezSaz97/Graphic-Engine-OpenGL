#include "types.h"

#ifndef __TEXTURES_ARRAY_H__
#define __TEXTURES_ARRAY_H__ 1

/**
 * @class TexturesArray
 *
 * @brief Represents a 2D texture with various options for wrapping and filtering.
 */
class TexturesArray
{
public:
  typedef uint32_t Id; ///< Type definition for the texture identifier.

  /**
   * @enum Wrap
   *
   * @brief Enumeration for texture wrap modes.
   */
  enum class Wrap : s16
  {
    Repeat = 0,      ///< Repeat texture coordinates.
    Mirrored_Repeat, ///< Repeat with mirroring.
    Clamp_To_Edge,   ///< Clamp to the edge.
    Clamp_To_Border  ///< Clamp to the border.
  };

  /**
   * @enum Filter
   *
   * @brief Enumeration for texture filtering modes.
   */
  enum class Filter
  {
    Linear = 0,            ///< Linear interpolation.
    Nearest,               ///< Nearest-neighbor interpolation.
    Linear_Mipmap_Linear,  ///< Linear interpolation with mipmapping.
    Linear_Mipmap_Nearest, ///< Linear interpolation with nearest-neighbor mipmapping.
    Nearest_Mipmap_Nearest ///< Nearest-neighbor interpolation with nearest-neighbor mipmapping.
  };

  /**
   * @brief Constructor for the TexturesArray class.
   *
   * @param wrapS Wrap mode for the S-axis.
   * @param wrapT Wrap mode for the T-axis.
   * @param minFilter Minification filter.
   * @param magFilters Magnification filter.
   */
  TexturesArray(Wrap wrapS = Wrap::Repeat, Wrap wrapT = Wrap::Repeat, Filter minFilter = Filter::Linear, Filter magFilters = Filter::Linear);

  /**
   * @brief Destructor for the TexturesArray class.
   */
  ~TexturesArray();

  /**
   * @brief Free all the resources
   */
  void free();

  /**
   * @brief Checks if the TexturesArray has a valid texture loaded.
   *
   * @return True if a texture is loaded, false otherwise.
   */
  boolean hasTexture() const;

  /**
   * @brief
   *
   * @param data
   * @param width
   * @param height
   * @param channels
  */
  static void InvertImageRows(u_byte* data, const s32 width, const s32 height, const s32 channels);

  /**
   * @brief Loads a texture from the specified file path.
   *
   * @param filePath Path to the image file.
   */
  void loadTexture(const std::string *files_path, const size_t &files_count);

  /**
   * @brief Gets the identifier of the texture.
   *
   * @return TexturesArray identifier.
   */
  u32 id();

  /**
   * @brief Gets the raw data of the texture.
   *
   * @return Pointer to the texture data.
   */
  u_byte* data(const size_t &layer) const;

  /**
   * @brief Gets the width of the texture.
   *
   * @return Width of the texture.
   */
  s32 width() const;

  /**
   * @brief Gets the height of the texture.
   *
   * @return Height of the texture.
   */
  s32 height() const;

  /**
   * @brief Gets the number of channels in the texture.
   *
   * @return Number of channels.
   */
  s32 channels(const size_t & layer) const;

private:
  u32 id_;              ///< TexturesArray identifier.
  u_byte** datas_;      ///< Raw texture data.
  u32 size_;            ///< Samplers count
  s32 width_, height_;  ///< Dimensions of the texture
  s32 *channels_;       ///< Number of color channels in the texture.
  boolean has_texture_; ///< Flag indicating whether a texture is loaded.
  Wrap wrapS_, wrapT_;  ///< Wrap modes for the S and T axes.
  Filter minF_, magF_;  ///< Minification and magnification filter modes.

  /**
   * @brief Loads texture data into OpenGL buffers.
   */
  void loadBuffers();
};

#endif /* __TEXTURES_ARRAY_H__ */