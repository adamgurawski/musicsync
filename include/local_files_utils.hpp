/**
 * This file contains functions used for operation on local files.
 */

#pragma once

#include "song.hpp"

#include <vector>

namespace ms
{
using Songs = std::vector<Song>;

namespace local_utils
{

/**
 * \return vector of found Songs
 * \param path path to directory which will be searched for files (and its subdirectories)
 * \param fileExtension extension of files to be searched for
 */
Songs ExtractSongs(const std::string& path, const std::string& fileExtension);

/**
 * \return vector storing names of found files (extensions are erased)
 * \param path path to directory where we will be looking for files (and its subdirectories)
 * \param extension file extension, e.g. ".mp3"
 */
std::vector<std::string> ExtractFilenames(const std::string& path,
  const std::string& extension);

} // namespace local_files
} // namespace ms