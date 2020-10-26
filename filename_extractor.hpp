#pragma once

#include <string>
#include <vector>

namespace ms
{

/**
 * This class is responsible for searching for files with appropriate extension in
 * specified path.
 */
class FilenameExtractor
{
public:
  /**
   * \param path path to directory where we will be looking for files (and its subdirectories)
   * \param extension file extension, e.g. ".mp3"
   * \return vector storing names of found files (extensions are erased)
   */
  static std::vector<std::string> ExtractFilenames(const std::string& path, 
    const std::string& extension);
};

} // namespace ms