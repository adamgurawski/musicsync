#pragma once

#include "song_info.hpp"

#include <string>
#include <vector>

namespace ms
{

/**
 * This class will be responsible for searching in local files for song titles.
 * 
 * For now, I think it would be passed directory path as parameter and then it would return
 * all songs in an STL container.
 */
class FileManager
{
public:
  using SongInfoCtr = std::vector<SongInfo>;
  
  /**
   * Return song info for all songs in specified directory.
   */
  static SongInfoCtr ExtractSongInfo(const std::string& path, const std::string& extension);
};

} // namespace ms