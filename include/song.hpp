#pragma once

#include <iostream>
#include <filesystem>
#include <string>

namespace ms
{

/**
 * TODO: AG: consider changing it into class.
 * Structure representing relevant info of a song. 
 */
struct Song
{
  std::string           Author;
  std::string           Title;
  // Absolute path of song file.
  std::filesystem::path AbsolutePath;
};

/// \return true if authors and titles are equal (case insensitive)
bool operator==(const Song& lhs, const Song& rhs);

inline std::ostream& operator<<(std::ostream& stream, const Song& song)
{
  stream << song.Author << " - " << song.Title << "\nAbsolute path: " << song.AbsolutePath;
  return stream;
}

} // namespace ms
