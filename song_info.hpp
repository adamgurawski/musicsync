#pragma once

#include <iostream>
#include <string>

namespace ms
{

/**
 * Structure representing relevant info of a song. 
 */
struct SongInfo
{
  std::string Author;
  std::string Title;
};

// AG: TODO: make the comparison case insensitive.
inline bool operator==(const SongInfo& lhs, const SongInfo& rhs)
{
  return lhs.Author == rhs.Author && lhs.Title == rhs.Title;
}

inline std::ostream& operator<<(std::ostream& stream, const SongInfo& songInfo)
{
  stream << songInfo.Author << " - " << songInfo.Title;
  return stream;
}

} // namespace ms
