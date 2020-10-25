#pragma once

#include "song_info.hpp"

namespace ms
{

struct FilenameParser
{
  // AG: TODO: comment me.
  static SongInfo Parse(const std::string& filename);
};

} // namespace ms
