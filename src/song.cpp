#include "song.hpp"

#include <algorithm>

namespace
{

/// Compare strings (case insensitive).
bool iequals(const std::string& lhs, const std::string& rhs)
{
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
    [](char left, char right)
    {
      return std::tolower(left) == std::tolower(right);
    });
}

} // anonymous namespace

namespace ms
{

bool operator==(const Song& lhs, const Song& rhs)
{
  // Return false if sizes do not match.
  if (lhs.Author.size() != rhs.Author.size() || lhs.Title.size() != rhs.Title.size())
    return false;

  return iequals(lhs.Author, rhs.Author) && iequals(lhs.Title, rhs.Title);
}

} // namespace ms