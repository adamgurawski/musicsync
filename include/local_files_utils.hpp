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
 * Get all music files with specified extension that are present in the directory specified by 
 * path (and in all subdirectories).
 * \return vector of Songs found in specified path
 * \param path path to directory which will be searched for files (and all subdirectories)
 * \param fileExtension extension of files to be searched for, e.g. ".mp3"
 */
Songs ExtractSongs(const std::string& path, const std::string& fileExtension);

/**
 * Get full path of every file present in specified path (and subdirectories).
 * \return vector storing full paths of found files
 * \param path path to directory where we will be looking for files (and all subdirectories)
 * \param extension target file extension, e.g. ".mp3"
 */
Paths ExtractFilePaths(const std::string& path, const std::string& extension);

} // namespace local_files
} // namespace ms