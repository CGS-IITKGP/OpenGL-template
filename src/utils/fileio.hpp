#if !defined(FILEIO_H)
#define FILEIO_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

/**
 * Get path of given file by traversing each directory in
 * the current directory and outer directories upto _MaxDepth levels
 *
 * @param _FileName name of file (can have partial path, like
 * "shaders/some.cool.shader.glsl")
 * @param _MaxDepth Number of directories to traverse up.
 * A _MaxDepth of 1 means the function will search current directory (and any
 * sub directories) and parent directory
 */
std::string fileio_getpath_r (const std::string &_FileName,
                              size_t _MaxDepth = 5);

#endif // FILEIO_H
