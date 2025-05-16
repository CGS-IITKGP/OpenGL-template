#if !defined(FILEIO_H)
#define FILEIO_H

#include <filesystem>
#include <iostream>
#include <string>

/**
 * @brief Retrieves the absolute path of a specified file by recursively searching
 * through the current directory and its parent directories.
 *
 * @param file_name The name of the file to locate. May include a partial path
 *                  (e.g., "shaders/some.cool.shader.glsl").
 * @param max_depth The maximum number of parent directories to traverse upward.
 *                  Default is 5. A value of 1 limits the search to the current
 *                  directory, its subdirectories, and the immediate parent directory.
 *
 * @return std::string The absolute path to the file if found, or an empty string
 *                     if the file cannot be located within the specified depth.
 */
std::string fileio_getpath(const std::string& file_name,
    size_t max_depth = 5);

#endif // FILEIO_H
