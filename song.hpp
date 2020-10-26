#pragma once

#include <iostream>
#include <string>

namespace ms
{

/**
 * // AG: TODO: consider changing it into class.
 * Structure representing relevant info of a song. 
 */
struct Song
{
  std::string Author;
  std::string Title;
  // AG: TODO: path?
};

// AG: TODO: make the comparison case insensitive.
inline bool operator==(const Song& lhs, const Song& rhs)
{
  return lhs.Author == rhs.Author && lhs.Title == rhs.Title;
}

inline std::ostream& operator<<(std::ostream& stream, const Song& songInfo)
{
  stream << songInfo.Author << " - " << songInfo.Title;
  return stream;
}

} // namespace ms
