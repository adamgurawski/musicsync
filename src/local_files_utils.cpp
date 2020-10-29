#include "local_files_utils.hpp"

#include <filesystem>

namespace
{
namespace fs = std::filesystem;

std::string GetFileNameWithoutExtension(const ms::local_utils::Path& path)
{
  return path.filename().replace_extension().string();
}

/**
 * Extract Song info from file path.
 */
ms::Song Parse(const ms::local_utils::Path& filePath)
{
  // Get file name.
  std::string fileName = GetFileNameWithoutExtension(filePath);
  // Get delimiter's positon - for now delimiter is set as " - ". It may change in the future.
  std::string delimiter = " - ";
  size_t delimiterPos = fileName.find(delimiter);

  // TODO: AG: throw if unable to find the delimiter?

  ms::Song result;
  result.Author = fileName.substr(0, delimiterPos);
  result.Title = fileName.substr(delimiterPos + delimiter.length());
  result.AbsolutePath = fs::absolute(filePath);
  return result;
}

/**
 * Call the callable on every file that is not a directory.
 */
template <typename Callable>
void PerformForEveryFile(fs::recursive_directory_iterator it, const std::string& extension,
  Callable callable)
{
  for (const auto& item : it)
  {
    if (item.is_directory() == false)
    {
      fs::path itemsPath{ item.path() };

      if (itemsPath.extension() == extension)
        callable(itemsPath);
    }
  }
}

} // anonymous namespace

namespace ms::local_utils
{

/**
 * TODO: AG: comment me.
 * Scan all files with given extension in specified path (and subdirectories if any exists).
 * \return
 */
Songs ExtractSongs(const std::string& path, const std::string& fileExtension)
{
  Paths songPaths = ExtractFilePaths(path, fileExtension);

  Songs result;

  for (const auto& path : songPaths)
    result.emplace_back(Parse(path));

  return result;
}

Paths ExtractFilePaths(const std::string& path, const std::string& extension)
{
  Path directoryPath { path };
  fs::recursive_directory_iterator directoryIt { directoryPath };

  Paths result;

  PerformForEveryFile(directoryIt, extension, [&](const Path& filePath) mutable
    {
      result.emplace_back(filePath);
    });

  return result;
}

} // namespace ms::local_files
