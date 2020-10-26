#pragma once

#include "song.hpp"

namespace ms
{

struct FilenameParser
{
  // AG: TODO: comment me.
  static Song Parse(const std::string& filename);
};

} // namespace ms
