#pragma once

#include <iostream>
#include <filesystem>
#include <string>

namespace ms
{

/**
 * // TODO: AG: consider changing it into class.
 * Structure representing relevant info of a song. 
 */
struct Song
{
  std::string           Author;
  std::string           Title;
  // Absolute path of song file.
  std::filesystem::path AbsolutePath;
};

// TODO: AG: make the comparison case insensitive.
inline bool operator==(const Song& lhs, const Song& rhs)
{
  return lhs.Author == rhs.Author && lhs.Title == rhs.Title;
}

inline std::ostream& operator<<(std::ostream& stream, const Song& song)
{
  stream << song.Author << " - " << song.Title << "\nAbsolute path: " << song.AbsolutePath;
  return stream;
}

} // namespace ms
