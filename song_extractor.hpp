#pragma once

#include "song.hpp"

#include <vector>

namespace ms
{
using Songs = std::vector<Song>;

struct SongExtractor
{
  /**
   * \param path path to directory which will be searched for files (and its subdirectories)
   * \param fileExtension extension of files to be searched for
   * \return vector of found Songs
   */
  static Songs ExtractSongs(const std::string& path, const std::string& fileExtension);
};

} // namespace ms