#include <string>

#ifndef __ERROR_LOG_H__
#define __ERROR_LOG_H__ 1

/**
 * @class ErrorLog
 *
 * @brief A class for managing error logs.
 */
class ErrorLog
{
public:
  /**
   * @struct Error
   *
   * @brief Structure representing an error entry.
   */
  class Error
  {
  public:
    std::string function_; ///< Name of the function where the error occurred.
    std::string error_;    ///< Description of the error.
    std::string line_;     ///< Line number where the error occurred.

    /**
     * @brief Default constructor for Error.
     */
    Error();

    /**
     * @brief Copy constructor for Error.
     *
     * @param other Another Error object to copy from.
     */
    Error(const Error &other);

    /**
     * @brief Constructor for Error with specified error, function, and line.
     *
     * @param error The error message.
     * @param function The name of the function where the error occurred.
     * @param line The line number where the error occurred.
     */
    Error(const std::string error, const std::string function = "\0", const std::string line = "\0");

    /**
     * @brief Destructor for Error.
     */
    ~Error();

    /**
     * @brief Assignment operator for Error.
     *
     * @param other Another Error object to assign from.
     * 
     * @return Error& A reference to the assigned Error object.
     */
    Error &operator=(const Error &other);
  };

  /**
   * @brief Constructor for the ErrorLog class.
   */
  ErrorLog();

  /**
   * @brief Destructor for the ErrorLog class.
   */
  ~ErrorLog();

  /**
   * @brief Add a new error entry to the end of the queue.
   *
   * @param error Description of the error.
   * @param function Name of the function where the error occurred.
   * @param line Line number where the error occurred.
   */
  void addError(std::string error = "\0", std::string function = "\0", std::string line = "\0");

  /**
   * @brief Get the last error from the queue and remove it.
   *
   * @return The last error entry.
   */
  Error getError();

private:
  Error *queue_; ///< Array storing error entries.
  size_t size_;  ///< Number of errors in the queue.
};

#endif /* __ERROR_LOG_H__ */
