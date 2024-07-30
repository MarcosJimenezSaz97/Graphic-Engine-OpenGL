#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__ 1

#include <iostream>
#include <string>

/**
 * @brief Structure representing the header of a file.
 */
struct Header
{
  char file_name_[256];     ///< Name of the file.
  char key_file_name_[256]; ///< Name of the key file.

  size_t file_data_size_; ///< Size of the file data.
};

/**
 * @brief Structure representing an array of files with their headers.
 */
struct FileArray
{
  Header *headers; ///< Array of file headers.

  std::string *files_data; ///< Array of file data.
  size_t files_count;      ///< Number of files in the array.
};

/**
 * @brief Load the source code of a file.
 *
 * @param file Path of the file to upload.
 *
 * @return A string of characters that represents the contents of the file.
 */
std::string LoadSourceFromFile(const char *file);

/**
 * @brief Save the source code into a file.
 *
 * @param file Path of the file to save.
 * @param save_data Data to be saved into the file.
 */
void SaveSourceInFile(const char *file, std::string save_data);

/**
 * @brief Load source code from a binary file.
 *
 * @param file Path of the binary file.
 *
 * @return A string containing the loaded source code.
 */
std::string LoadSourceFromBinary(const char *file);

/**
 * @brief Save source code into a binary file.
 *
 * @param file Path of the binary file to save.
 * @param save_data Source code to be saved.
 */
void SaveSourceInBinary(const char *file, std::string save_data);

/**
 * @brief Group files into a binary file.
 *
 * @param file_array FileArray containing files and their headers.
 * @param name_no_extension Name of the binary file without extension.
 */
void GroupFilesInBinary(const FileArray &file_array, const char *name_no_extension);

/**
 * @brief Load grouped files from a binary file.
 *
 * @param name_no_extension Name of the binary file without extension.
 *
 * @return The loaded FileArray containing files and their headers.
 */
const FileArray LoadGroupFilesBinary(const char *name_no_extension);

/**
 * @brief Load data from an encrypted binary file.
 *
 * @param encrypted_file Path of the encrypted binary file.
 * @param file Path of the file to decrypt.
 * @param key_file Path of the key file.
 *
 * @return Decrypted data as a string.
 */
std::string LoadDataFromEncryptedBinary(const char *encrypted_file, const char *file, const char *key_file);

/**
 * @brief Change the extension of a file.
 *
 * @param file File path.
 * @param new_extension New extension to set.
 *
 * @return The file path with the new extension.
 */
std::string ChangeExtension(const std::string &file, const std::string &new_xtension);

/**
 * @brief Extracts the filename from a file path.
 *
 * @param file File path.
 *
 * @return The filename extracted from the file path.
 */
std::string SubstractPath(const std::string &file);

/**
 * @brief Generate random keys.
 *
 * @param width Width of the keys.
 * @param height Height of the keys.
 *
 * @return Pointer to the generated random keys.
 */
unsigned char *GenRandomKeys(size_t width, size_t height);

/**
 * @brief Write keys into a PGM file.
 *
 * @param file Path of the PGM file.
 * @param keys Pointer to the keys.
 * @param width Width of the keys.
 * @param height Height of the keys.
 */
void WritePGM(const char *file, unsigned char *keys, size_t width, size_t height);

/**
 * @brief Load keys from a PGM file.
 *
 * @param file Path of the PGM file.
 * @param width Output parameter to store the width of the keys.
 * @param height Output parameter to store the height of the keys.
 *
 * @return Pointer to the loaded keys.
 */
unsigned char *LoadKeyFromPGM(const char *file, size_t &width, size_t &height);

/**
 * @brief Encrypt data using a key file.
 *
 * @param decrypted_data Data to encrypt.
 * @param key_file Path of the key file.
 *
 * @return Encrypted data as a string.
 */
std::string EncryptData(std::string decrypted_data, const char *key_file);

/**
 * @brief Decrypt encrypted data using a key file.
 *
 * @param encrypted_data Encrypted data to decrypt.
 * @param key_file Path of the key file.
 *
 * @return Decrypted data as a string.
 */
std::string DecryptData(std::string encrypted_data, const char *key_file);

/**
 * @brief Structure for holding configuration file data.
 */
typedef struct
{
  int count;     ///< Number of values in the configuration file.
  float *values; ///< Array of floating-point values.
} FConfigFileData;

/**
 * @brief Load a array of values setted in a config file
 *
 * To use is need to have some rules.
 * In the file you need to write the value name and the values (If have more than one)
 * Examples ->
 *  Health: 10
 *  Str: 1.2
 *  Vel: 12, 20.5, 7
 *
 * @param file Path of the file to read.
 * @param var_name value name.
 *
 * @return A array of values and the count
 * Take into acount that you can have more than one value per line.
 */
FConfigFileData ReadVarFromFile(const char *file, const char *var_name);

/**
 * @brief Structure for holding configuration file data.
 */
typedef struct
{
  int count;     ///< Number of values in the configuration file.
  char **values; ///< Array of C-style strings (character arrays).
} CConfigFileData;

/**
 * @brief Load an array of strings set in a config file
 *
 * To use is need to have some rules.
 * In the file you need to write the value name and the values (If have more than one)
 * Examples ->
 *  Health: good, excellent
 *  Str: strong, weak
 *  Vel: fast, moderate, slow
 *
 * @param file Path of the file to read.
 * @param var_name value name.
 *
 * @return A array of strings and the count
 * Take into account that you can have more than one value per line.
 */
CConfigFileData ReadStringFromFile(const char *file, const char *var_name);

#endif /* __FILEMANAGER_H__ */