/**
 * This file contains functions used for operation on local files.
 */

#pragma once

#include "song.hpp"

#include <filesystem>
#include <vector>

namespace ms
{
using Songs = std::vector<Song>;

namespace local_utils
{
using Path = std::filesystem::path;
using Paths = std::vector<Path>;

/**
 * \return vector of found Songs
 * \param path path to directory which will be searched for files (and its subdirectories)
 * \param fileExtension extension of files to be searched for
 */
Songs ExtractSongs(const std::string& path, const std::string& fileExtension);

/**
 * TODO: AG: update comment.
 * \return vector storing paths of found files
 * \param path path to directory where we will be looking for files (and its subdirectories)
 * \param extension file extension, e.g. ".mp3"
 */
Paths ExtractFilePaths(const std::string& path, const std::string& extension);

} // namespace local_files
} // namespace ms